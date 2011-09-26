game {
  player {
    name: "Andy"
    state {
      last_bid: 2
    }
    loans: 4
    cash: 8
  }
  player {
    name: "Beth"
    state {
      auction_pass_order: 1
    }
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
}
selected_action: 0
result {
  player {
    name: "Andy"
    loans: 4
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
  phase: PHASE_TAKE_POWERS
  state {
    current_bid: 2
  }
}
