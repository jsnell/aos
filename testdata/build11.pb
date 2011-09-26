game {
  player {
    state {
    }
    cash: 10
    color: COLOR_RED
  }
  player {
    color: COLOR_BLUE
  }
  order: 0
  order: 1
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
        }
      }
      hex {
      }
      hex {
      }
      hex {
        city_index: 1
      }
    }
  }
  terrain {
    build_cost: 2
  }
}
expected_options {
  action {
    build_in {
      location {
        row: 0
        col: 2
      }
    }
  }
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
