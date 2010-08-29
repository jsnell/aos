#include "gen/aos.pb.h"
#include "loans.h"

#include <iostream>
#include <string>

#include <google/gflags.h>
#include <glog/logging.h>
#include <google/protobuf/text_format.h>

DEFINE_string(mode, "", "");
DEFINE_string(phase, "", "");
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

  if (FLAGS_mode == "opt") {
    Options opt;
    if (FLAGS_phase == "loan") {
      opt.MergeFrom(loan_options(game, FLAGS_player_index));
    } else {
      LOG(FATAL) << "Invalid phase " << FLAGS_phase;
    }
    google::protobuf::TextFormat::PrintToString(opt, &out);
  } else if (FLAGS_mode == "act") {
    Options opt;
    if (!google::protobuf::TextFormat::ParseFromString(FLAGS_options_pb, &opt))
      LOG(FATAL) << "Error parsing Options pb:\n"
                 << FLAGS_options_pb;      

    if (FLAGS_action_index < 0 || FLAGS_action_index > opt.action_size()) {
      LOG(FATAL) << "Invalid index " << FLAGS_action_index;
    }

    const Action& action = opt.action(FLAGS_action_index);

    if (FLAGS_phase == "loan") {
      loan_action(&game, action, FLAGS_player_index);
    } else {
      LOG(FATAL) << "Invalid phase " << FLAGS_phase;
    }
    google::protobuf::TextFormat::PrintToString(game, &out);
  } else {
    LOG(FATAL) << "Invalid mode " << FLAGS_mode;
  }
  
  std::cout << out << "\n";

  return 0;
}
