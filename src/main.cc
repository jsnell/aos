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

#include <iostream>
#include <string>

#include "dispatch.h"
#include <google/gflags.h>
#include <glog/logging.h>
#include <google/protobuf/text_format.h>
#include "render.h"

using std::string;

DEFINE_int32(mode, 0, "");
DEFINE_int32(player_index, -1, "");

DEFINE_string(game_pb, "", "");
DEFINE_string(options_pb, "", "");
DEFINE_int32(action_index, -1, "");

int main(int argc, char **argv) {
    google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging("aos");

    CHECK(argc == 1) << "Non-flag arguments on command line";

    CHECK(!FLAGS_game_pb.empty());

    Game game;
    if (!google::protobuf::TextFormat::ParseFromString(FLAGS_game_pb, &game)) {
        LOG(FATAL) << "Error parsing Game pb:\n"
                   << FLAGS_game_pb;
    }

    if (FLAGS_player_index < 0 || FLAGS_player_index > game.player_size()) {
        LOG(FATAL) <<  "Invalid index " << FLAGS_player_index;
    }

    Options opt;
    if (!FLAGS_options_pb.empty()) {
        if (!google::protobuf::TextFormat::ParseFromString(FLAGS_options_pb,
                                                           &opt)) {
            LOG(FATAL) << "Error parsing Options pb:\n"
                       << FLAGS_options_pb;
        }
    }

    dispatch(&game, &opt, (DispatchMode) FLAGS_mode,
             FLAGS_player_index, FLAGS_action_index);

    string out;

    if (FLAGS_mode == DISPATCH_OPT) {
        google::protobuf::TextFormat::PrintToString(opt, &out);
    } else if (FLAGS_mode == DISPATCH_ACT) {
        google::protobuf::TextFormat::PrintToString(game, &out);
    } else if (FLAGS_mode == DISPATCH_RENDER) {
        out = render_game(game, opt);
    } else {
        LOG(FATAL) << "Invalid mode " << FLAGS_mode;
    }

    std::cout << out << "\n";

    return 0;
}
