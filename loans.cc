#include "gen/aos.pb.h"

Options loan_options(const Game& game, int player_index) {
  Options res;
  const Player& player = game.player(player_index);

  for (int i = 0; i <= (15 - player.loans()); ++i)
    res.add_action()->mutable_loans()->set_loans_to_take(i);

  return res;
}

void loan_action(Game* game, const Action& action, int player_index) {
  Player* player = game->mutable_player(player_index);
  int loans_to_take = action.loans().loans_to_take();
  player->set_loans(player->loans() + loans_to_take);
  player->set_cash(player->cash() + loans_to_take * 5);  
}
