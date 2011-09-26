game {
  player {
    state {
      queued_build {
        build_in {
          location {
            row: 0
            col: 2
          }
          track {
            from {
              row: 0
              col: 1
            }
            to {
              row: 0
              col: 3
            }
            owner_index: 0
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
        col: 4
      }
    }
  }
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
    state {
      queued_build {
        build_in {
          location {
            row: 0
            col: 2
          }
          track {
            from {
              row: 0
              col: 1
            }
            to {
              row: 0
              col: 3
            }
            owner_index: 0
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
