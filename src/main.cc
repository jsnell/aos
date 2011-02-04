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

  Game game;
  if (!google::protobuf::TextFormat::ParseFromString(FLAGS_game_pb, &game)) {
    LOG(FATAL) << "Error parsing Game pb:\n"
               << FLAGS_game_pb;
  }

  if (FLAGS_player_index < 0 || FLAGS_player_index > game.player_size()) {
    LOG(FATAL) <<  "Invalid index " << FLAGS_player_index;
  }

  string out;

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
