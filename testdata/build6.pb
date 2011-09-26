game {
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
      queued_build {
        build_in {
          location {
            row: 0
            col: 1
          }
        }
      }
      queued_build {
        build_in {
          location {
            row: 0
            col: 1
          }
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
          cost: 4
        }
      }
    }
    cash: 10
    color: COLOR_BLUE
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
    build_finish: true
  }
  action {
    build_undo: true
  }
}
selected_action: 0
result {
  player {
    cash: 6
    color: COLOR_BLUE
  }
  order: 0
  current_order_index: 0
  phase: PHASE_MOVE
  map {
    row {
      hex {
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
