#include "gen/aos.pb.h"
#include "dispatch.h"

#include <cstdio>
#include <glog/logging.h>

class AuctionHandler : public Handler{
public:
  Options options(const Game& game, int player_index) {
    Options res;
    const Player& player = game.player(player_index);
    
    res.add_action()->mutable_bid()->set_pass(true);
  
    int passed_count = 0;
    for (int i = 0; i < game.player_size(); ++i)
      if (game.player(i).state().has_auction_pass_order())
        ++passed_count;

    if (passed_count < (game.player_size() - 1)) {
      int current_bid = game.state().current_bid();
      if (current_bid &&
          current_bid == player.state().last_bid())
        res.add_action()->mutable_bid()->set_amount(current_bid);
      for (int i = current_bid + 1; i <= player.cash(); ++i)
        res.add_action()->mutable_bid()->set_amount(i);
    }

    return res;
  }

  void act(Game* game, const Action& action, int player_index) {
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
      game->mutable_state()->set_current_bid(action.bid().amount());
    }

    if (passed_count == game->player_size()) {
      game->set_current_order_index(0);
      game->set_phase(PHASE_TAKE_POWERS);
      return;
    }

    int start = game->current_order_index() + 1;

    for (int count = 0; count < game->order_size(); ++count) {
      int index = (count + start) % game->order_size();
      if (!game->player(index).state().has_auction_pass_order()) {
        game->set_current_order_index(index);
        return;
      }
    }

    LOG(FATAL) << "Can't happen.";
  }
};

static bool register_me = register_handler(new AuctionHandler(),
                                           PHASE_AUCTION);
