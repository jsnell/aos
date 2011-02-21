game {
    player {
        cash: 10
        state {
          queued_build {
            build_in {
              location {
                row: 0 col: 1
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
        hex { city { color: COLOR_RED } }
        hex { }
        hex { }
      }
    }
}
expected_options {
    action {
        build_in {
            location { row: 0 col: 1 }
            track { from { row: 0 col: 0 } to { row: 0 col: 2} owner_index: 0 }
        }
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
                col: 1
              }
              track {
                from { row: 0 col: 0 }
                to { row: 0 col: 2 }
                owner_index: 0 
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
        hex { city { color: COLOR_RED } }
        hex { }
        hex { }
      }
    }
}
