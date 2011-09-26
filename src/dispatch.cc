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

#include <map>

typedef std::map<int, Handler*> HandlerMap;
static HandlerMap* handler_map() {
    static HandlerMap* map = new HandlerMap();
    return map;
}

bool register_handler(Handler* handler, int phase) {
    (*handler_map())[phase] = handler;
    return true;
}

void dispatch(Game* game,
              Options* options,
              DispatchMode mode,
              int player_index,
              int action_index) {
    if (player_index < 0 || player_index > game->player_size())
        LOG(FATAL) <<  "Invalid index " << player_index;

    Handler* handler = (*handler_map())[game->phase()];
    CHECK(handler) <<  "Invalid phase " << game->phase();

    if (mode == DISPATCH_OPT) {
        options->MergeFrom(handler->options(*game, player_index));
    } else if (mode == DISPATCH_ACT) {
        CHECK(action_index < options->action_size()) << "Invalid action index "
                                                     << action_index;
        const Action& action = options->action(action_index);

        handler->act(game, action, player_index);
    } else if (mode == DISPATCH_RENDER) {
    } else if (mode == DISPATCH_APPLY_PHASE_STATE) {
        handler->apply_phase_state(game, player_index);
    } else {
        LOG(FATAL) << "Invalid mode " << mode;
    }
}
