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

#include "map_util.h"

bool location_eq(const Location& a, const Location& b) {
    return a.row() == b.row() && a.col() == b.col();
}

const Hex& location_hex(const Game& game, const Location& location) {
    return game.map().row(location.row()).hex(location.col());
}

Hex* mutable_location_hex(Game* game, const Location& location) {
    return game->mutable_map()->mutable_row(location.row())->
        mutable_hex(location.col());
}


const Track* track_in_a_pointing_to_b(const Game& game,
                                      const Location& a,
                                      const Location& b) {
    const Hex& a_hex = location_hex(game, a);

    for (int i = 0; i < a_hex.track_size(); ++i) {
        const Track& track = a_hex.track(i);
        if (location_eq(track.from(), b) ||
            location_eq(track.to(), b)) {
            return &track;
        }
    }

    return NULL;
}

Track* mutable_track_in_a_pointing_to_b(Game* game,
                                        const Location& a,
                                        const Location& b) {
    Hex* a_hex = mutable_location_hex(game, a);

    for (int i = 0; i < a_hex->track_size(); ++i) {
        Track* track = a_hex->mutable_track(i);
        if (location_eq(track->from(), b) ||
            location_eq(track->to(), b)) {
            return track;
        }
    }

    return NULL;
}
