#include "dispatch.h"

#include <glog/logging.h>
#include <vector>

using std::vector;

class BuildHandler : public Handler {
  typedef vector<Location> LocationVector;

  Options options(const Game& orig_game, int player_index) {
    Game game(orig_game);
    Options res;
    Player* player = game.mutable_player(player_index);

    int queued = player->state().queued_build_size();

    // TODO: Urbanization
    // TODO: Redirect track
    // TODO: Undo

    if (!queued) {
      location_options(game, *player, &res);
      res.add_action()->set_build_finish(true);
    } else {  
      apply_phase_state(&game, player);

      BuildInAction act = player->state().queued_build(queued-1).build_in();
      if (act.track_size()) {
        if (queued < max_builds(game, *player)) {
          location_options(game, *player, &res);
        }
        res.add_action()->set_build_finish(true);
      } else {
        track_options(game, *player, act, &res);
      }
    }        

    return res;
  }

  int max_builds(const Game& game, const Player& player) {
    if (player.power() == POWER_ENGINEER) {
      return 4;
    }

    return 3;
  }

  void apply_phase_state(Game* game, Player* player) {
    for (int i = 0; i < player->state().queued_build_size(); ++i) {
      BuildInAction act = player->state().queued_build(i).build_in();
      for (int j = 0; j < act.track_size(); ++j) {
        game->mutable_map()->mutable_row(act.location().row())->
          mutable_hex(act.location().col())->
          add_track()->CopyFrom(act.track(j));
      }
      if (act.track_size()) {
        player->set_cash(player->cash() - act.cost());
      }
    }
  }

  void track_options(const Game& game, const Player& player,
                     const BuildInAction& act, Options* res) {
    const Location& loc = act.location();
    LocationVector n = neighbors(game, player, loc.row(), loc.col());

    for (LocationVector::iterator it = n.begin(); it != n.end(); ++it) {
      for (LocationVector::iterator jt = it + 1; jt != n.end(); ++jt) {
        if (it == jt)
          continue;

        // TODO: check for existing track
        // TODO: check for trying to connect two rail heads owned by different
        // players

        BuildInAction* new_act = res->add_action()->mutable_build_in();
        new_act->CopyFrom(act);
        Track* track = new_act->add_track();
        track->mutable_from()->CopyFrom(*it);
        track->mutable_to()->CopyFrom(*jt);
      }
    }
  }

  void location_options(const Game& game, const Player& player,
                        Options* res) {
    const Map& map = game.map();

    for (int row = 0; row < map.row_size(); ++row) {
      for (int col = 0; col < map.row(row).hex_size(); ++col) {
        bool add = false;

        const Hex& current = map.row(row).hex(col);

        if (current.has_city())
          continue;

        int cost = game.terrain(current.terrain_index()).build_cost();

        // TODO: terrain cost not always relevant (e.g. complex upgrades)
        if (cost > player.cash())
          continue;

        // FIXME: need to handle complex track
        if (current.track_size())
          continue;

        LocationVector adjacent = neighbors(game, player, row, col);
        for (unsigned int i = 0; i < adjacent.size(); ++i) {
          const Location& n = adjacent[i];
          const Hex& nhex = map.row(n.row()).hex(n.col());

          // If the current hex contains track leading to that neighbor,
          // it might be possible to build to that hex.
          for (int j = 0; j < nhex.track_size(); ++j) {
            const Track& track = nhex.track(j);
            if (track.from().row() == row &&
                track.from().col() == col) {
              add = true;
            }
            if (track.to().row() == row &&
                track.to().col() == col) {
              add = true;
            }
          }

          const Hex& hex = map.row(n.row()).hex(n.col());
          if (hex.has_city()) {
            add = true;
          }
        }

        if (add) {
          Location* loc = res->add_action()->mutable_build_in()->
            mutable_location();
          loc->set_row(row);
          loc->set_col(col);
        }
      }
    }
  }

  // The map looks like this:
  //
  //   0 1 2 3 4 5
  //    0 1 * 3 4 5
  //   0 1 2 3 4 5
  //    0 1 2 3 4 5
  //
  // So 1,2 is adjacent to 0,2; 0,3; 1,1; 1,3; 2,2: 2,3.
  LocationVector neighbors(const Game& game, const Player& player,
                           int row, int col) {
    LocationVector n;
    int base_col = col + (row % 2);

    // Previous row
    if (row != 0) {
      if (base_col > 0) {
        n.push_back(location(row - 1, base_col - 1));
      }
      if (base_col < game.map().row(row).hex_size() - 1) {
        n.push_back(location(row - 1, base_col));
      }
    } 

    // Same row
    if (col != 0) {
      n.push_back(location(row, col - 1));
    }
    if (col != game.map().row(row).hex_size() - 1) {
      n.push_back(location(row, col + 1));
    }

    // Next row
    if (row != game.map().row_size() - 1) {
      if (base_col > 0) {
        n.push_back(location(row + 1, base_col - 1));
      }
      if (base_col < game.map().row(row).hex_size() - 1) {
        n.push_back(location(row + 1, base_col));
      }
    }

    // TODO: filter out occupied hexes, unpassable hex-sides.

    return n;
  }

  void add_hex(const Hex& hex, const Location& loc, Options* res) {
    Location* add = res->add_action()->mutable_build_in()->mutable_location();
    add->CopyFrom(loc);
  }

  Location location(int row, int col) {
    Location res;
    res.set_row(row);
    res.set_col(col);
    return res;
  }

  void act(Game* game, const Action& action, int player_index) {
    Player* player = game->mutable_player(player_index);
    if (action.has_build_in()) {
      if (action.build_in().track_size()) {
        Action* build = player->mutable_state()->
          mutable_queued_build(player->state().queued_build_size() - 1);
        build->CopyFrom(action);
      } else {
        player->mutable_state()->add_queued_build()->CopyFrom(action);
      }
    }
    // TODO: (remove old track)
    if (action.build_finish()) {
      apply_phase_state(game, player);
      player->clear_state();
      
      int index = game->current_order_index() + 1;
      if (index == game->player_size()) {
        game->set_current_order_index(0);
        game->set_phase(PHASE_MOVE);
      } else {
        game->set_current_order_index(index);
      }
    }
  }

};

static bool register_me = register_handler(new BuildHandler(),
                                           PHASE_BUILD);
