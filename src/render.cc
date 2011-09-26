// -*- c-basic-offset: 4 -*-
//
// Copyright (C) 2011 by Juho Snellman. Standard MIT license:
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "render.h"

#include <iostream>

#include "ctemplate/template.h"
#include "dispatch.h"
#include <google/gflags.h>
#include <glog/logging.h>

using std::string;
using ctemplate::Template;
using ctemplate::TemplateDictionary;

DEFINE_string(game_template, "", "");

string map_color(Color color) {
    switch (color) {
    case COLOR_RED: return "red";
    case COLOR_GREEN: return "green";
    case COLOR_BLUE: return "blue";
    case COLOR_YELLOW: return "yellow";
    case COLOR_PURPLE: return "purple";
    case COLOR_BLACK: return "black";
    case COLOR_NONE: return "none";
    }

    LOG(FATAL) << "Unknown color " << color;
}

string map_power(Power power) {
    switch (power) {
    case POWER_FIRST_BUILD: return "First build";
    case POWER_FIRST_MOVE: return "First move";
    case POWER_ENGINEER: return "Engineer";
    case POWER_LOCOMOTIVE: return "Locomotive";
    case POWER_URBANIZATION: return "Urbanization";
    case POWER_PRODUCTION: return "Production";
    case POWER_TURN_ORDER: return "Turn order";
    case POWER_NONE: return "No special power";
    }

    LOG(FATAL) << "Unknown power " << power;
}

void fill_player(const Player& player, bool is_current,
                 TemplateDictionary* dict) {
    dict->SetValue("NAME", player.name());
    dict->SetIntValue("LOANS", player.loans());
    dict->SetIntValue("CASH", player.cash());
    dict->SetIntValue("LINK_LEVEL", player.link_level());
    dict->SetValue("POWER", map_power(player.power()));
    dict->SetValue("COLOR", map_color(player.color()));
    if (is_current) {
        dict->AddSectionDictionary("ACTIVE");
    }
}

void fill_order(const Player& player, bool is_current,
                TemplateDictionary* dict) {
    dict->SetValue("COLOR", map_color(player.color()));
    dict->SetValue("ACTIVE", is_current ? "true" : "false");
}

void fill_map(const Game& game, TemplateDictionary* dict) {
    const Map& map = game.map();
    for (int r = 0; r < map.row_size(); ++r) {
        const MapRow& row = map.row(r);
        for (int c = 0; c < row.hex_size(); ++c) {
            const Hex& hex = row.hex(c);
            TemplateDictionary* hexdict = dict->AddSectionDictionary("HEX");
            hexdict->SetIntValue("ROW", r);
            hexdict->SetIntValue("COL", c);
            hexdict->SetIntValue("TERRAIN", hex.terrain_index());
            if (hex.has_city_index()) {
                TemplateDictionary* citydict =
                    hexdict->AddSectionDictionary("CITY");
                citydict->SetValue(
                    "COLOR",
                    map_color(game.city(hex.city_index()).color()));
            }

            if (hex.has_town() &&
                !hex.has_city_index()) {
                TemplateDictionary* towndict =
                    hexdict->AddSectionDictionary("TOWN");
                towndict->SetIntValue("EXISTS", 1);
            }

            for (int i = 0; i < hex.track_size(); ++i) {
                TemplateDictionary* trackdict =
                    hexdict->AddSectionDictionary("TRACK");
                const Track& track = hex.track(i);
                trackdict->SetIntValue("FROM_ROW", track.from().row());
                trackdict->SetIntValue("FROM_COL", track.from().col());
                trackdict->SetIntValue("TO_ROW", track.to().row());
                trackdict->SetIntValue("TO_COL", track.to().col());

                string color;
                if (track.has_owner_index()) {
                    color =
                        map_color(game.player(track.owner_index()).color());
                } else {
                    color = map_color(COLOR_NONE);
                }
                trackdict->SetValue("COLOR", color);
            }
        }
    }
}

void fill_game(const Game& orig_game, TemplateDictionary* dict) {
    Game game(orig_game);

    for (int i = 0; i < game.player_size(); ++i) {
        Options options;
        dispatch(&game, &options, DISPATCH_APPLY_PHASE_STATE, i, 0);
    }

    for (int i = 0; i < game.order_size(); ++i) {
        TemplateDictionary* player = dict->AddSectionDictionary("PLAYER");
        fill_player(game.player(game.order(i)),
                    i == game.current_order_index(),
                    player);
    }

    for (int i = 0; i < game.order_size(); ++i) {
        TemplateDictionary* order = dict->AddSectionDictionary("ORDER");

        fill_order(game.player(game.order(i)),
                   i == game.current_order_index(),
                   order);
    }

    fill_map(game, dict);
}

void fill_options(const Options& opt,
                  TemplateDictionary* dict) {
    dict->SetValue("OPTIONS", opt.DebugString());
}

string render_game(const Game& game,
                   const Options &options) {
    CHECK(!FLAGS_game_template.empty());

    TemplateDictionary dict("game");
    fill_game(game, &dict);
    fill_options(options, &dict);

    Template* tpl = Template::GetTemplate(FLAGS_game_template,
                                          ctemplate::STRIP_BLANK_LINES);

    string output;
    CHECK(tpl->Expand(&output, &dict));
    return output;
}
