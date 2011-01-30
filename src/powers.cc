#include "dispatch.h"

#include <algorithm>
#include <set>

#include <glog/logging.h>

class TakePowersHandler : public Handler {
  Options options(const Game& game, int player_index) {
    Options res;
    std::set<int> taken;

    for (int i = 0; i < game.player_size(); ++i) {
      if (game.player(i).has_power())
        taken.insert(game.player(i).power());
    }

    for (int i = 0; i < game.power_size(); ++i) {
      if (taken.find(game.power(i)) == taken.end())
        res.add_action()->mutable_take_power()->set_power(game.power(i));
    }

    return res;
  }

  void act(Game* game, const Action& action, int player_index) {
    Player* player = game->mutable_player(player_index);
    Power power = action.take_power().power();
    player->set_power(power);

    if (power == POWER_LOCOMOTIVE) {
      player->set_link_level(std::min(6, player->link_level() + 1));
    }

    int index = game->current_order_index() + 1;

    if (index == game->player_size()) {
      game->set_current_order_index(0);
      game->set_phase(PHASE_BUILD);
    } else {
      game->set_current_order_index(index);
    }
  }
};

static bool register_me = register_handler(new TakePowersHandler(),
                                           PHASE_TAKE_POWERS);
