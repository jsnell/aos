game {
  player {
    state {
      last_bid: 3
    }
    cash: 5
  }
  player {
    state {
      auction_pass_order: 0
    }
  }
  player {
    state {
      auction_pass_order: 1
    }
  }
  player {
  }
  player {
  }
  order: 0
  order: 1
  order: 2
  order: 3
  order: 4
  current_order_index: 0
  phase: PHASE_AUCTION
  state {
    current_bid: 10
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
    state {
      auction_pass_order: 2
      last_bid: 3
    }
    cash: 3
  }
  player {
    state {
      auction_pass_order: 0
    }
  }
  player {
    state {
      auction_pass_order: 1
    }
  }
  player {
  }
  player {
  }
  order: 0
  order: 1
  order: 2
  order: 3
  order: 4
  current_order_index: 3
  phase: PHASE_AUCTION
  state {
    current_bid: 10
  }
}
