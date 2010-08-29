#include "dispatch.h"
#include "loans.h"

#include <glog/logging.h>

void dispatch(Game* game,
              Options* options,
              const std::string& mode,
              const std::string& phase,
              int player_index,
              int action_index) {
  if (player_index < 0 || player_index > game->player_size())
    LOG(FATAL) <<  "Invalid index " << player_index;

  if (mode == "opt") {
    if (phase == "loan")
      options->MergeFrom(loan_options(*game, player_index));
    else
      LOG(FATAL) << "Invalid phase " << phase;
  } else if (mode == "act") {
    if (action_index < 0 || action_index > options->action_size())
      LOG(FATAL) << "Invalid index " << action_index;

    const Action& action = options->action(action_index);

    if (phase == "loan")
      loan_action(game, action, player_index);
    else
      LOG(FATAL) << "Invalid phase " << phase;
  } else {
    LOG(FATAL) << "Invalid mode " << mode;
  }
}
