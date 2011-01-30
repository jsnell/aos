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

void fill_player(const Player& player,
                 TemplateDictionary* dict) {  
  dict->SetValue("NAME", player.name());
  dict->SetIntValue("LOANS", player.loans());
  dict->SetIntValue("CASH", player.cash());
  dict->SetIntValue("LINK_LEVEL", player.link_level());
  dict->SetValue("POWER", map_power(player.power()));
  dict->SetValue("COLOR", map_color(player.color()));
}

void fill_order(const Player& player, bool is_current,
                TemplateDictionary* dict) {  
  dict->SetValue("COLOR", map_color(player.color()));
  dict->SetValue("ACTIVE", is_current ? "true" : "false");
}

void fill_game(const Game& game,
               TemplateDictionary* dict) {
  for (int i = 0; i < game.player_size(); ++i) {
    TemplateDictionary* player = dict->AddSectionDictionary("PLAYER");
    fill_player(game.player(i), player);
  }

  for (int i = 0; i < game.order_size(); ++i) {
    TemplateDictionary* order = dict->AddSectionDictionary("ORDER");

    fill_order(game.player(game.order(i)),
               i == game.current_order_index(),
               order);
  }
}

string render_game(const Game& game) {
  TemplateDictionary dict("game");
  fill_game(game, &dict);

  Template* tpl = Template::GetTemplate(FLAGS_game_template,
                                        ctemplate::STRIP_BLANK_LINES);
                    
  string output;
  CHECK(tpl->Expand(&output, &dict));
  return output;
}
