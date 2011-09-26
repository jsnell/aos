game {
  player {
    name: "Andy"
    state {
      last_bid: 2
    }
    loans: 4
    cash: 3
  }
  player {
    name: "Beth"
    loans: 3
    cash: 2
  }
  order: 0
  order: 1
  current_order_index: 0
  phase: PHASE_AUCTION
  state {
    current_bid: 2
  }
}
expected_options {
  action {
    bid {
      pass: true
    }
  }
  action {
    bid {
      amount: 2
    }
  }
  action {
    bid {
      amount: 3
    }
  }
}
selected_action: 1
result {
  player {
    name: "Andy"
    state {
      last_bid: 2
    }
    loans: 4
    cash: 3
  }
  player {
    name: "Beth"
    loans: 3
    cash: 2
  }
  order: 0
  order: 1
  current_order_index: 1
  phase: PHASE_AUCTION
  state {
    current_bid: 2
  }
}
