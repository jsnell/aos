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
        color: COLOR_RED
    }
    player { color: COLOR_BLUE }
    order: 0
    order: 1
    current_order_index: 0
    phase: PHASE_BUILD
    map {
      row {
        hex { city { color: COLOR_RED } }
        hex { track { from { row: 0 col: 0 } to { row: 0 col: 2 } } }
        hex { }
        hex { }
      }
    }
    terrain { build_cost: 2 }
}
expected_options {
  action {
    build_finish: true
  }
  action { build_undo: true }
}
selected_action: 0
result {
player {
  cash: 10
  color: COLOR_RED
}
player {
  color: COLOR_BLUE
}
order: 0
order: 1
current_order_index: 1
phase: PHASE_BUILD
map {
  row {
    hex {
      city {
        color: COLOR_RED
      }
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
    hex {
    }
  }
}
terrain {
  build_cost: 2
}
}
