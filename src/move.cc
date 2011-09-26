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

    virtual void apply_phase_state(Game* game, int player_index) {
    }
};

static bool register_me = register_handler(new MoveHandler(),
                                           PHASE_MOVE);
