#include "auction.h"

#include <glog/logging.h>

Options auction_options(const Game& game, int player_index) {
  Options res;
  const Player& player = game.player(player_index);

  res.add_action()->mutable_bid()->set_pass(true);

  int passed_count = 0;
  for (int i = 0; i < game.player_size(); ++i)
    if (game.player(i).state().has_auction_pass_order())
      ++passed_count;

  if (passed_count < (game.player_size() - 1)) {
    for (int i = game.state().current_bid() + 1;
         i <= player.cash(); ++i)
      res.add_action()->mutable_bid()->set_amount(i);
  }

  return res;
}

void auction_action(Game* game, const Action& action, int player_index) {
  Player* player = game->mutable_player(player_index);

  int passed_count = 0;
  for (int i = 0; i < game->player_size(); ++i)
    if (game->player(i).state().has_auction_pass_order())
      ++passed_count;

  if (action.bid().pass()) {
    player->mutable_state()->set_auction_pass_order(passed_count + 1);

    // Pay.
    int cash = player->cash();
    if (passed_count == 0)
      // First to pass pays nothing.
      ;
    else if (passed_count >= (game->player_size() - 2))
      // Last two to pass pay full.
      cash -= player->state().last_bid();
    else
      // Others pay half their bid, rounded up
      cash -= (player->state().last_bid() + 1) / 2;

    player->set_cash(cash);
    passed_count++;
  } else {
    player->mutable_state()->set_last_bid(action.bid().amount());
  }

  int index = game->current_order_index() + 1;

  if (passed_count == game->player_size()) {
    game->set_current_order_index(0);
    game->set_phase("power");
  } else if (index == game->player_size()) {
    game->set_current_order_index(0);
  } else {
    game->set_current_order_index(index);
  }
}
