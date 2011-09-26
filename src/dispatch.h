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

#include "aos.pb.h"
#include <string>

class Handler {
  public:
    virtual ~Handler() {}

    virtual Options options(const Game& game, int player_index) = 0;
    virtual void act(Game* game, const Action& action, int player_index) = 0;
    virtual void apply_phase_state(Game* game, int player_index) = 0;
};

enum DispatchMode {
    DISPATCH_OPT = 1,
    DISPATCH_ACT = 2,
    DISPATCH_RENDER = 3,
    DISPATCH_APPLY_PHASE_STATE = 4,
};

bool register_handler(Handler* handler, int phase);

void dispatch(Game* game,
              Options* options,
              DispatchMode mode,
              int player_index,
              int action_index);

