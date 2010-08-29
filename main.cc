#include "gen/aos.pb.h"
#include "dispatch.h"

#include <iostream>
#include <string>

#include <google/gflags.h>
#include <glog/logging.h>
#include <google/protobuf/text_format.h>

DEFINE_string(mode, "", "");
DEFINE_int32(player_index, -1, "");

DEFINE_string(game_pb, "", "");
DEFINE_string(options_pb, "", "");
DEFINE_int32(action_index, -1, "");

int main(int argc, char **argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging("aos");

  Game game;
  if (!google::protobuf::TextFormat::ParseFromString(FLAGS_game_pb, &game))
    LOG(FATAL) << "Error parsing Game pb:\n"
               << FLAGS_game_pb;

  if (FLAGS_player_index < 0 || FLAGS_player_index > game.player_size())
    LOG(FATAL) <<  "Invalid index " << FLAGS_player_index;

  std::string out;

  Options opt;
  if (!FLAGS_options_pb.empty())
    if (!google::protobuf::TextFormat::ParseFromString(FLAGS_options_pb, &opt))
      LOG(FATAL) << "Error parsing Options pb:\n"
                 << FLAGS_options_pb;      

  dispatch(&game, &opt, FLAGS_mode, FLAGS_player_index, FLAGS_action_index);

  if (FLAGS_mode == "opt") {
    google::protobuf::TextFormat::PrintToString(opt, &out);
  } else if (FLAGS_mode == "act") {
    google::protobuf::TextFormat::PrintToString(game, &out);
  } else {
    LOG(FATAL) << "Invalid mode " << FLAGS_mode;
  }
  
  std::cout << out << "\n";

  return 0;
}
