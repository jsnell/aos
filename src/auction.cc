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

#include "dispatch.h"

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
            player->mutable_state()->set_auction_pass_order(passed_count);

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
            for (int i = 0; i < game->player_size(); ++i) {
                int pass_order = game->player(i).state().auction_pass_order();
                game->set_order(game->player_size() - pass_order, i);
                game->mutable_player(i)->clear_state();
            }
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

    void apply_phase_state(Game* game, int player_index) {
    }
};

static bool register_me = register_handler(new AuctionHandler(),
                                           PHASE_AUCTION);
