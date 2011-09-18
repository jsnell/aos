game {
    player {
        name: "Andy"
    }
    player {
        name: "Beth"
	state { link_increased: true }
    }
    order: 0
    order: 1
    current_order_index: 1
    phase: PHASE_MOVE
    state { movement_round: 1 }
}
expected_options {
  action {
    move {
      pass: true
    }
  }  
}
selected_action: 0
result {
    player {
        name: "Andy"
    }
    player {
        name: "Beth"
    }
    order: 0
    order: 1
    current_order_index: 0
    phase: PHASE_PRODUCE
}
