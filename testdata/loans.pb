game {
  player {
    name: "Andy"
    loans: 10
    cash: 6
  }
  player {
    name: "Beth"
    loans: 3
    cash: 2
  }
  order: 0
  order: 1
  current_order_index: 0
  phase: PHASE_TAKE_LOANS
}
expected_options {
  action {
    loans {
      loans_to_take: 0
    }
  }
  action {
    loans {
      loans_to_take: 1
    }
  }
  action {
    loans {
      loans_to_take: 2
    }
  }
  action {
    loans {
      loans_to_take: 3
    }
  }
  action {
    loans {
      loans_to_take: 4
    }
  }
  action {
    loans {
      loans_to_take: 5
    }
  }
}
selected_action: 2
result {
  player {
    name: "Andy"
    loans: 12
    cash: 16
  }
  player {
    name: "Beth"
    loans: 3
    cash: 2
  }
  order: 0
  order: 1
  current_order_index: 1
  phase: PHASE_TAKE_LOANS
}
