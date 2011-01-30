#include "aos.pb.h"
#include <string>

class Handler {
  public:
    virtual ~Handler() {}

    virtual Options options(const Game& game, int player_index) = 0;
    virtual void act(Game* game, const Action& action, int player_index) = 0;
};

enum DispatchMode {
    DISPATCH_OPT = 1,
    DISPATCH_ACT = 2,
    DISPATCH_RENDER = 3,
};

bool register_handler(Handler* handler, int phase);

void dispatch(Game* game,
              Options* options,
              DispatchMode mode,
              int player_index,
              int action_index);

