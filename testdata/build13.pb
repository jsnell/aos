game {
    player {
        cash: 10
        state {
        }
        color: COLOR_RED
    }
    player { color: COLOR_BLUE }
    order: 0
    order: 1
    current_order_index: 0
    phase: PHASE_BUILD
    map {
      row {
        hex { city_index: 0 }
        hex { track { from { row: 0 col: 0 } to { row: 0 col: 2 } } }
        hex { track { from { row: 0 col: 1 } to { row: 0 col: 3 } } }
        hex { track { from { row: 0 col: 2 } to { row: 0 col: 4 } } }
        hex { track { from { row: 0 col: 3 } to { row: 0 col: 5 } } }
        hex { }
        hex { }
        hex { }
        hex { track { from { row: 0 col: 7 } to { row: 0 col: 9 } } }
        hex { track { from { row: 0 col: 8 } to { row: 0 col: 10 } } }
        hex { track { from { row: 0 col: 9 } to { row: 0 col: 11 } } }
        hex { }
        hex { }
      }
    }
    terrain { build_cost: 2 }
}
expected_options {
action {
  build_in {
    location {
      row: 0
      col: 5
    }
  }
}
action {
  build_finish: true
}
}

