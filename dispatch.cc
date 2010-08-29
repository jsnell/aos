#include "dispatch.h"
#include "loans.h"
#include "auction.h"

#include <glog/logging.h>

void dispatch(Game* game,
              Options* options,
              const std::string& mode,
              int player_index,
              int action_index) {
  int phase = game->phase();

  if (player_index < 0 || player_index > game->player_size())
    LOG(FATAL) <<  "Invalid index " << player_index;

  if (mode == "opt") {
    if (phase == PHASE_TAKE_LOANS)
      options->MergeFrom(loan_options(*game, player_index));
    else if (phase == PHASE_AUCTION)
      options->MergeFrom(auction_options(*game, player_index));
    else
      LOG(FATAL) << "Invalid phase " << phase;
  } else if (mode == "act") {
    if (action_index < 0 || action_index > options->action_size())
      LOG(FATAL) << "Invalid index " << action_index;

    const Action& action = options->action(action_index);

    if (phase == PHASE_TAKE_LOANS)
      loan_action(game, action, player_index);
    else if (phase == PHASE_AUCTION)
      auction_action(game, action, player_index);
    else
      LOG(FATAL) << "Invalid phase " << phase;
  } else {
    LOG(FATAL) << "Invalid mode " << mode;
  }
}
