game {
  player {
    cash: 10
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
        city_index: 0
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
}
expected_options {
  action {
    build_in {
      location {
        row: 0
        col: 1
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
selected_action: 0
result {
  player {
    state {
      queued_build {
        build_in {
          location {
            row: 0
            col: 1
          }
        }
      }
    }
    cash: 10
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
        city_index: 0
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
}
