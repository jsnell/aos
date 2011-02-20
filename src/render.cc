#include "render.h"

#include <iostream>

#include "ctemplate/template.h"
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

void fill_map(const Map& map, TemplateDictionary* dict) {
  for (int r = 0; r < map.row_size(); ++r) {
    const MapRow& row = map.row(r);
    for (int c = 0; c < row.hex_size(); ++c) {
      const Hex& hex = row.hex(c);
      TemplateDictionary* hexdict = dict->AddSectionDictionary("HEX");
      hexdict->SetIntValue("ROW", r);
      hexdict->SetIntValue("COL", c);
      hexdict->SetIntValue("TERRAIN", hex.terrain());
      if (hex.has_city()) {
        TemplateDictionary* citydict = hexdict->AddSectionDictionary("CITY");
        citydict->SetValue("COLOR", map_color(hex.city().color()));
      }
      
      for (int i = 0; i < hex.track_size(); ++i) {
        TemplateDictionary* trackdict = hexdict->AddSectionDictionary("TRACK");
        const Track& track = hex.track(i);
        trackdict->SetIntValue("FROM_ROW", track.from().row());
        trackdict->SetIntValue("FROM_COL", track.from().col());
        trackdict->SetIntValue("TO_ROW", track.to().row());
        trackdict->SetIntValue("TO_COL", track.to().col());
      }
    }
  }
}

void fill_game(const Game& game, TemplateDictionary* dict) {
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

  fill_map(game.map(), dict);
}

void fill_options(const Options& opt,
                  TemplateDictionary* dict) {
  dict->SetValue("OPTIONS", opt.DebugString());
}

string render_game(const Game& game,
                   const Options &options) {
  TemplateDictionary dict("game");
  fill_game(game, &dict);
  fill_options(options, &dict);

  Template* tpl = Template::GetTemplate(FLAGS_game_template,
                                        ctemplate::STRIP_BLANK_LINES);
                    
  string output;
  CHECK(tpl->Expand(&output, &dict));
  return output;
}
