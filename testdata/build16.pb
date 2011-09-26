game {
  player {
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
          owner_index: -1
        }
      }
      hex {
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
