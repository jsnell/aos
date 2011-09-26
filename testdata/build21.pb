game {
  player {
    state {
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
        city_index: 0
      }
      hex {
        track {
          from {
            row: 0
            col: 0
          }
          to {
            row: 0
            col: 2
          }
          owner_index: 0
        }
      }
      hex {
        track {
          from {
            row: 0
            col: 2
          }
          to {
            row: 0
            col: 1
          }
          owner_index: 0
        }
        track {
          from {
            row: 0
            col: 2
          }
          to {
            row: 0
            col: 3
          }
        }
        has_town: true
      }
      hex {
      }
      hex {
      }
    }
  }
  terrain {
    build_cost: 2
  }
  city {
  }
}
expected_options {
  action {
    build_in {
      location {
        row: 0
        col: 3
      }
    }
  }
  action {
    build_finish: true
  }
}
