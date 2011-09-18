#include "dispatch.h"

class MoveHandler : public Handler {
  Options options(const Game& game, int player_index) {
    Options res;
    const Player& player = game.player(player_index);

    if (!player.state().link_increased()) {
      res.add_action()->mutable_move()->set_increase_link(true);
    }

    res.add_action()->mutable_move()->set_pass(true);

    return res;
  }

  void act(Game* game, const Action& action, int player_index) {
    Player* player = game->mutable_player(player_index);

    if (action.move().increase_link()) {
      player->set_link_level(player->link_level() + 1);
      player->mutable_state()->set_link_increased(true);
    }

    int index = game->current_order_index() + 1;
    if (index == game->player_size()) {
      int round = game->state().movement_round();
      if (round == 1) {
	game->set_current_order_index(0);
	game->set_phase(PHASE_PRODUCE);
	for (int i = 0; i < game->player_size(); ++i) {
	  game->mutable_player(i)->clear_state();
	}
	game->clear_state();
      } else {
	game->set_current_order_index(0);
	game->mutable_state()->set_movement_round(round + 1);
      }
    } else {
      game->set_current_order_index(index);
    }
  }
};

static bool register_me = register_handler(new MoveHandler(),
                                           PHASE_MOVE);
