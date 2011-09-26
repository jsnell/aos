game {
  player {
    state {
      auction_pass_order: 0
    }
  }
  player {
    state {
      last_bid: 2
    }
    cash: 3
  }
  player {
    state {
      auction_pass_order: 1
    }
  }
  player {
    state {
      last_bid: 1
    }
    cash: 3
  }
  player {
    state {
      auction_pass_order: 2
    }
  }
  order: 0
  order: 1
  order: 2
  order: 3
  order: 4
  current_order_index: 3
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
      amount: 3
    }
  }
}
selected_action: 1
result {
  player {
    state {
      auction_pass_order: 0
    }
  }
  player {
    state {
      last_bid: 2
    }
    cash: 3
  }
  player {
    state {
      auction_pass_order: 1
    }
  }
  player {
    state {
      last_bid: 3
    }
    cash: 3
  }
  player {
    state {
      auction_pass_order: 2
    }
  }
  order: 0
  order: 1
  order: 2
  order: 3
  order: 4
  current_order_index: 1
  phase: PHASE_AUCTION
  state {
    current_bid: 3
  }
}
