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

class TakeLoansHandler : public Handler {
    Options options(const Game& game, int player_index) {
        Options res;
        const Player& player = game.player(player_index);

        for (int i = 0; i <= (15 - player.loans()); ++i)
            res.add_action()->mutable_loans()->set_loans_to_take(i);

        return res;
    }

    void act(Game* game, const Action& action, int player_index) {
        Player* player = game->mutable_player(player_index);
        int loans_to_take = action.loans().loans_to_take();
        player->set_loans(player->loans() + loans_to_take);
        player->set_cash(player->cash() + loans_to_take * 5);

        int index = game->current_order_index() + 1;

        if (index == game->player_size()) {
            game->set_current_order_index(0);
            game->set_phase(PHASE_AUCTION);
        } else {
            game->set_current_order_index(index);
        }
    }

    void apply_phase_state(Game* game, int player_index) {
    }
};

static bool register_me = register_handler(new TakeLoansHandler(),
                                           PHASE_TAKE_LOANS);
