game {
    player {
        name: "Andy"
    }
    player {
        name: "Beth"
    }
    order: 0
    order: 1
    current_order_index: 0
    phase: PHASE_MOVE
}
expected_options {
  action {
    move {
      increase_link: true
    }
  }
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
	link_level: 2
	state { link_increased: true }
    }
    player {
        name: "Beth"
    }
    order: 0
    order: 1
    current_order_index: 1
    phase: PHASE_MOVE
}