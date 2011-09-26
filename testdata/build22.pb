game {
    player {
        cash: 10
	state {
	}
    }
    order: 0
    current_order_index: 0
    phase: PHASE_BUILD
    map {
      row {
        hex { city_index: 0 }
        hex { track { owner_index: 0 from { row: 0 col: 0 } to { row: 0 col: 2 } } }
        hex {
          has_town: true
          track { from { row: 0 col: 2 } to { row: 0 col: 3 } }
        }
        hex { }
        hex { }
      }
    }
    city {
    }
    terrain {
        build_cost: 2
    }
}
expected_options {
  action {
    build_in { location { row: 0 col: 2 } }
  }
  action { build_finish: true }
}
