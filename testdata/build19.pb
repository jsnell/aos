game {
    player {
        cash: 10
	power: POWER_URBANIZATION
	state {
  	  queued_build {
            build_in {
                location { row: 0 col: 3 }
  	        urbanize_city_index: 1
		cost: 0
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
        hex { track { owner_index: 2 from { row: 0 col: 1 } to { row: 0 col: 3 } } }
        hex { has_town: true track { owner_index: 2 from { row: 0 col: 2 } } }
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
  action { build_finish: true }
  action { build_undo: true }
}
selected_action: 0
result {
    player {
        cash: 10
	power: POWER_URBANIZATION
    }
    order: 0
    current_order_index: 0
    phase: PHASE_MOVE
    map {
      row {
        hex { }
        hex { }
        hex { track { owner_index: 2 from { row: 0 col: 1 } to { row: 0 col: 3 } } }
        hex { has_town: false city_index: 1 }
        hex { }
      }
    }
    city {
       name: "A"
       available_for_urbanize: true
    }
    city {
       name: "B"
       available_for_urbanize: false
    }
    terrain {
        build_cost: 2
    }
}
