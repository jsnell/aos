game {
    player {
        cash: 10
        state {
          queued_build {
            build_in {
              location {
                row: 0
                col: 2
              }
              track {
                from { row: 0 col: 1 }
                to { row: 0 col: 3 }
              }
              cost: 3
            }
          }
          queued_build {
            build_in {
              location {
                row: 0
                col: 1
              }
              track {
                from { row: 0 col: 0 }
                to { row: 0 col: 2 }
              }
              cost: 2
            }
          }
        }
    }
    player {}
    player {}
    order: 0
    order: 1
    order: 2
    current_order_index: 0
    phase: PHASE_BUILD
    map {
      row {
        hex { }
        hex { }
        hex { }
        hex { city { color: COLOR_RED } }
        hex { }
        hex { }
      }
    }
    terrain { build_cost: 2 }
}
expected_options {
    action {
        build_in {
            location { row: 0 col: 4 }
        }
    }
    action {
        build_finish: true
    }
}
selected_action: 1
result {
    player {
        cash: 5
    }
    player {}
    player {}
    order: 0
    order: 1
    order: 2
    current_order_index: 1
    phase: PHASE_BUILD
    map {
      row {
        hex { }
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
          track {
            from {
              row: 0
              col: 1
            }
            to {
              row: 0
              col: 3
            }
          }
        }
        hex { city { color: COLOR_RED } }
        hex { }
        hex { }
      }
    }
    terrain { build_cost: 2 }
}
