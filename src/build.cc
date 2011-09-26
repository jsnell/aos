#include "dispatch.h"

#include <glog/logging.h>
#include <set>
#include <utility>
#include <vector>

using std::make_pair;
using std::pair;
using std::set;
using std::string;
using std::vector;

class BuildHandler : public Handler {
  typedef vector<Location> LocationVector;

  Options options(const Game& orig_game, int player_index) {
    Game game(orig_game);
    Options res;
    Player* player = game.mutable_player(player_index);

    int queued = player->state().queued_build_size();

    // TODO: Redirect track

    if (!queued) {
      location_options(game, player_index, &res);
      res.add_action()->set_build_finish(true);
    } else {  
      apply_phase_state(&game, player_index);

      BuildInAction act = player->state().queued_build(queued-1).build_in();
      if (act.track_size() || act.has_urbanize_city_index()) {
        if (queued < max_builds(game, *player)) {
          location_options(game, player_index, &res);
        }
        res.add_action()->set_build_finish(true);
      } else {
        track_options(game, player_index, act, &res);
      }

      res.add_action()->set_build_undo(true);
    }        

    return res;
  }

  int max_builds(const Game& game, const Player& player) {
    // Free urbanization needs to be handled somewhere. Here or in options()?

    if (player.power() == POWER_ENGINEER) {
      return 4;
    }

    return 3;
  }

  virtual void apply_phase_state(Game* game, int player_index) {
    Player* player = game->mutable_player(player_index);
    for (int i = 0; i < player->state().queued_build_size(); ++i) {
      BuildInAction act = player->state().queued_build(i).build_in();
      Hex* hex = game->mutable_map()->mutable_row(act.location().row())->
        mutable_hex(act.location().col());
      
      for (int j = 0; j < act.track_size(); ++j) {
	hex->add_track()->CopyFrom(act.track(j));
	maybe_claim_neutral_track(game, player_index, act.location(),
				  act.track(j).to());
	maybe_claim_neutral_track(game, player_index, act.location(),
				  act.track(j).from());
      }
      if (act.track_size()) {
        player->set_cash(player->cash() - act.cost());
      }
      if (act.has_urbanize_city_index()) {
	hex->set_has_town(false);
	hex->set_city_index(act.urbanize_city_index());
	hex->clear_track();
	player->mutable_state()->set_used_urbanization(true);
	game->mutable_city(act.urbanize_city_index())->
	  set_available_for_urbanize(false);
	
	LocationVector n = neighbors(*game, *player,
				     act.location().row(), act.location().col());
	for (LocationVector::iterator it = n.begin(); it != n.end(); ++it) {
	  maybe_claim_neutral_track(game, player_index, act.location(), *it);
	}
      }
    }
  }

  // Return:
  //   0 if player can't build track against source in build_loc
  //   1 if player is not prevented from building, but needs access
  //   2 if player gets access to building in build_loc through source
  int check_ok_to_build(const Game& game, int player_index,
                        const Location& build_loc,
                        const Location& source) {
    const Hex& source_hex = game.map().row(source.row()).hex(source.col());

    if (source_hex.has_city_index()) {
      return 2;
    }

    if (track_in_a_pointing_to_b(&game, build_loc, source))
      return 0;

    const Track* track = track_in_a_pointing_to_b(&game, source, build_loc);

    if (track) {
      if (location_eq(track->from(), build_loc) ||
          location_eq(track->to(), build_loc)) {
        if (track->owner_index() == player_index) {
          return 2;
        } else if (track->owner_index() == -1) {
	  if (route_traces_to_city_or_connected_town(game,
						     build_loc,
						     source,
						     player_index)) {
	    return 2;
	  }
	  return 1;
	} else {
          return 0;
        }
      }
    }

    return 1;
  }

  const Track* track_in_a_pointing_to_b(const Game* game,
					const Location& a,
					const Location& b) {
    const Hex& a_hex = game->map().row(a.row()).hex(a.col());

    for (int i = 0; i < a_hex.track_size(); ++i) {
      const Track& track = a_hex.track(i);
      if (location_eq(track.from(), b) ||
          location_eq(track.to(), b)) {
	return &track;
      }
    }

    return NULL;
  }

  Track* mutable_track_in_a_pointing_to_b(Game* game,
					  const Location& a,
					  const Location& b) {
    Hex* a_hex = game->mutable_map()->mutable_row(a.row())->mutable_hex(a.col());

    for (int i = 0; i < a_hex->track_size(); ++i) {
      Track* track = a_hex->mutable_track(i);
      if (location_eq(track->from(), b) ||
          location_eq(track->to(), b)) {
	return track;
      }
    }

    return NULL;
  }

  bool route_traces_to_city_or_connected_town(const Game& game,
					      const Location& start,
					      const Location& towards,
					      int player_index) {
    const Track* track = track_in_a_pointing_to_b(&game, towards, start);

    if (!track) {
      // Means there's a link that's disconnected at both ends.
      // Shouldn't happen, but maybe there's some wacky variant.
      return false;
    }

    const Location& track_dest =
      (track->from().row() == start.row() &&
       track->from().col() == start.col()) ?
      track->to() : track->from();

    const Hex& target_hex =
      game.map().row(track_dest.row()).hex(track_dest.col());

    if (target_hex.has_city_index()) {
      return true;
    }

    if (target_hex.has_town()) {
      for (int i = 0; i < target_hex.track_size(); ++i) {
        const Track& track = target_hex.track(i);
        if (track.owner_index() == player_index)
          return true;
      }

      return false;
    }

    return route_traces_to_city_or_connected_town(game, towards,
						  track_dest, player_index);
  }

  bool location_has_town(const Game& game, const Location& loc) {
    const Hex& hex = game.map().row(loc.row()).hex(loc.col());

    return hex.has_town();
  }

  bool location_eq(const Location& a, const Location&b) {
    return a.row() == b.row() && a.col() == b.col();
  }

  void maybe_claim_neutral_track(Game* game, int player_index,
				 const Location& start,
				 const Location& towards) {
    Track* track = mutable_track_in_a_pointing_to_b(game, towards, start);

    if (!track) {
      return;
    }

    if (track->owner_index() != -1) {
      return;
    }
    track->set_owner_index(player_index);

    const Location& track_dest =
      (track->from().row() == start.row() &&
       track->from().col() == start.col()) ?
      track->to() : track->from();

    maybe_claim_neutral_track(game, player_index, towards, track_dest);
  }

  void town_track_options(const Game& game, int player_index,
			  const BuildInAction& act, Options* res) {
    const Player& player = game.player(player_index);
    const Location& loc = act.location();
    LocationVector n = neighbors(game, player, loc.row(), loc.col());

    if (player.power() == POWER_URBANIZATION &&
	!player.state().used_urbanization()) {
      for (int i = 0; i < game.city_size(); ++i) {
	if (game.city(i).available_for_urbanize()) {
	  BuildInAction* new_act = res->add_action()->mutable_build_in();
	  new_act->CopyFrom(act);
	  new_act->set_urbanize_city_index(i);
	  new_act->set_cost(0);
	}
      }
    }

    set<int> combined;
    set<int> all;

    for (unsigned int i = 0; i < n.size(); ++i) {
      int status = check_ok_to_build(game, player_index, loc, n[i]);

      if (status == 1) {
        all.insert(1 << i);
      }
      if (status == 2) {
        all.insert(1 << i);
        combined.insert(1 << i);
      }
    }

    for (int i = 0; i < 4; ++i) {
      set<int> copy(combined);

      for (set<int>::iterator it = copy.begin(); it != copy.end(); ++it) {
        for (set<int>::iterator jt = all.begin(); jt != all.end(); ++jt) {
          combined.insert(*it | *jt);
        }
      }
    }

    for (set<int>::iterator it = combined.begin(); it != combined.end(); ++it) {
      BuildInAction* new_act = res->add_action()->mutable_build_in();
      new_act->CopyFrom(act);

      for (unsigned int i = 0; i < n.size(); ++i) {
        if ((*it) & (1 << i)) {
          Track* track = new_act->add_track();
          track->mutable_from()->CopyFrom(loc);
          track->mutable_to()->CopyFrom(n[i]);
          track->set_owner_index(player_index);
        }
      }
    }
  }

  void clear_track_options(const Game& game, int player_index,
			   const BuildInAction& act, Options* res) {
    const Player& player = game.player(player_index);
    const Location& loc = act.location();
    LocationVector n = neighbors(game, player, loc.row(), loc.col());

    for (unsigned int i = 0; i < n.size(); ++i) {
      int istatus = check_ok_to_build(game, player_index, loc, n[i]);
      // LOG(ERROR) << it->DebugString() << " status: " << istatus;

      for (unsigned int j = i + 1; j < n.size(); ++j) {
	int jstatus = check_ok_to_build(game, player_index, loc, n[j]);

	// Require at least one 2 and for both to be non-zero.
	if (istatus * jstatus < 2) {
	  continue;
	}
        
	// TODO: check for existing track

	BuildInAction* new_act = res->add_action()->mutable_build_in();
	new_act->CopyFrom(act);
	Track* track = new_act->add_track();
	track->mutable_from()->CopyFrom(n[i]);
	track->mutable_to()->CopyFrom(n[j]);
	track->set_owner_index(player_index);
      }
    }

    // TODO: Track piece limits.

    int len = res->action_size();
    for (int i = 0; i < len; ++i) {
      if (res->action(i).build_in().track_size() > 1) {
	continue;
      }

      const Track& itrack = res->action(i).build_in().track(0);
      set<string> used_edges;
      used_edges.insert(itrack.from().DebugString());
      used_edges.insert(itrack.to().DebugString());

      for (int j = i; j < len; ++j) {
	if (res->action(j).build_in().track_size() > 1) {
	  continue;
	}

	const Track& jtrack = res->action(j).build_in().track(0);

	if (used_edges.find(jtrack.from().DebugString()) == used_edges.end() &&
	    used_edges.find(jtrack.to().DebugString()) == used_edges.end()) {
	  BuildInAction* new_act = res->add_action()->mutable_build_in();
	  new_act->CopyFrom(res->action(i).build_in());

	  Track* track = new_act->add_track();
	  track->CopyFrom(jtrack);
	}
      }
    }
  }

  void track_options(const Game& game, int player_index,
                     const BuildInAction& act, Options* res) {
    const Player& player = game.player(player_index);
    const Location& loc = act.location();
    const Hex& hex = game.map().row(loc.row()).hex(loc.col());
    LocationVector n = neighbors(game, player, loc.row(), loc.col());

    if (hex.has_city_index()) {
      return;
    } else if (hex.has_town()) { 
      town_track_options(game, player_index, act, res);
    } else {
      clear_track_options(game, player_index, act, res);
    }
  }

  void location_options(const Game& game, int player_index, Options* res) {
    const Player& player = game.player(player_index);
    const Map& map = game.map();

    for (int row = 0; row < map.row_size(); ++row) {
      for (int col = 0; col < map.row(row).hex_size(); ++col) {
        const Hex& current = map.row(row).hex(col);

        if (current.has_city_index())
          continue;

        int cost = game.terrain(current.terrain_index()).build_cost();

        // TODO: terrain cost not always relevant (e.g. complex upgrades)
        if (cost > player.cash())
          continue;

        // Get the build options in this location:
        Location loc;
        loc.set_row(row);
        loc.set_col(col);
        BuildInAction fake_act;
        Options fake_opt;
        fake_act.mutable_location()->CopyFrom(loc);
        track_options(game, player_index, fake_act, &fake_opt);

        // If none, skip
        if (!fake_opt.action_size())
          continue;

        res->add_action()->mutable_build_in()->mutable_location()->
          CopyFrom(loc);
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
    int row_size = game.map().row(row).hex_size();

    // Previous row
    if (row != 0) {
      if (base_col > 0) {
        n.push_back(location(row - 1, base_col - 1));
      }
      if (base_col < row_size) {
        n.push_back(location(row - 1, base_col));
      }
    } 

    // Same row
    if (col != 0) {
      n.push_back(location(row, col - 1));
    }
    if (col != row_size - 1) {
      n.push_back(location(row, col + 1));
    }

    // Next row
    if (row != game.map().row_size() - 1) {
      if (base_col > 0) {
        n.push_back(location(row + 1, base_col - 1));
      }
      if (base_col < row_size) {
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
      if (action.build_in().track_size() ||
	  action.build_in().has_urbanize_city_index()) {
        Action* build = player->mutable_state()->
          mutable_queued_build(player->state().queued_build_size() - 1);
        build->CopyFrom(action);
      } else {
        player->mutable_state()->add_queued_build()->CopyFrom(action);
      }
    }
    // TODO: (remove orphaned track). Or maybe remove it at the start
    // of a player's action? Should be isomorphic, but easier to check.
    if (action.build_finish()) {
      apply_phase_state(game, player_index);
      player->clear_state();
      
      int index = game->current_order_index() + 1;
      if (index == game->player_size()) {
        game->set_current_order_index(0);
        game->set_phase(PHASE_MOVE);
      } else {
        game->set_current_order_index(index);
      }
    }
    if (action.build_undo()) {
      player->clear_state();
    }
  }

};

static bool register_me = register_handler(new BuildHandler(),
                                           PHASE_BUILD);
