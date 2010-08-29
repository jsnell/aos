#include "gen/aos.pb.h"
#include <string>

void dispatch(Game* game,
              Options* options,
              const std::string& mode,
              int player_index,
              int action_index);
