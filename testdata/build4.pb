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
            }          
          }
        }
    }
    order: 0
    current_order_index: 0
    phase: PHASE_BUILD
    map {
      row {
        hex { }
        hex { }
        hex { }
        hex { city: true }
        hex { }
        hex { }
      }
    }
}
expected_options {
    action {
        build_in {
            location { row: 0 col: 1 }
        }
    }                
    action {
        build_in {
            location { row: 0 col: 4 }
        }
    }
    action {
        build_finish: true
    }
}
selected_action: 0
result {
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
    }
    order: 0
    current_order_index: 0
    phase: PHASE_BUILD
    map {
      row {
        hex { }
        hex { }
        hex { }
        hex { city: true }
        hex { }
        hex { }
      }
    }
}