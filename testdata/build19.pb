game {
  player {
    state {
      queued_build {
        build_in {
          location {
            row: 0
            col: 3
          }
          cost: 0
          urbanize_city_index: 1
        }
      }
    }
    cash: 10
    power: POWER_URBANIZATION
  }
  order: 0
  current_order_index: 0
  phase: PHASE_BUILD
  map {
    row {
      hex {
      }
      hex {
      }
      hex {
        track {
          from {
            row: 0
            col: 1
          }
          to {
            row: 0
            col: 3
          }
          owner_index: 2
        }
      }
      hex {
        track {
          from {
            row: 0
            col: 2
          }
          owner_index: 2
        }
        has_town: true
      }
      hex {
      }
    }
  }
  terrain {
    build_cost: 2
  }
  city {
    name: "A"
    available_for_urbanize: true
  }
  city {
    name: "B"
    available_for_urbanize: true
  }
}
expected_options {
  action {
    build_finish: true
  }
  action {
    build_undo: true
  }
}
selected_action: 0
result {
  player {
    cash: 10
    power: POWER_URBANIZATION
  }
  order: 0
  current_order_index: 0
  phase: PHASE_MOVE
  map {
    row {
      hex {
      }
      hex {
      }
      hex {
        track {
          from {
            row: 0
            col: 1
          }
          to {
            row: 0
            col: 3
          }
          owner_index: 2
        }
      }
      hex {
        city_index: 1
        has_town: false
      }
      hex {
      }
    }
  }
  terrain {
    build_cost: 2
  }
  city {
    name: "A"
    available_for_urbanize: true
  }
  city {
    name: "B"
    available_for_urbanize: false
  }
}
