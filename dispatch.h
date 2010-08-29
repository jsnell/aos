#include "gen/aos.pb.h"
#include <string>

void dispatch(Game* game,
              Options* options,
              const std::string& mode,
              const std::string& phase,
              int player_index,
              int action_index);
