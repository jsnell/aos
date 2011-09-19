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
        hex {  }
        hex { track { from { row: 0 col: 0 } to { row: 0 col: 2 } } }
        hex { }
        hex { }
        hex { city_index: 0 }
      }
    }
    terrain { build_cost: 2 }
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

