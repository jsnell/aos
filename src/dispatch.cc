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
