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
        hex { }
        hex { }
        hex { track { owner_index: -1 from { row: 0 col: 1 } to { row: 0 col: 3 } } }
        hex { has_town: true }
        hex { }
      }
    }
    city {
       name: "A"
       available_for_urbanize: true
    }
    city {
       name: "B"
       available_for_urbanize: true
    }
    terrain {
        build_cost: 2
    }
}
expected_options {
    action {
        build_in {
            location { row: 0 col: 3 }
        }
    }                
    action { build_finish: true }
}
