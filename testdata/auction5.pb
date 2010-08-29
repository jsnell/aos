game {
    player {
        state { auction_pass_order: 1 }
    }
    player {
        cash: 3
        state { last_bid: 2 }
    }
    player {
        state { auction_pass_order: 2 }
    }
    player {
        cash: 3
        state { last_bid: 1 }
    } 
    player {
        state { auction_pass_order: 3 }
    } 
    order: 0
    order: 1
    order: 2
    order: 3
    order: 4
    current_order_index: 3
    phase: "auction"
    state { current_bid: 2 }
}
expected_options {
    action { bid { pass: true } }
    action { bid { amount: 3 } }
}
selected_action: 1
result {
    player {
        state { auction_pass_order: 1 }
    }
    player {
        cash: 3
        state { last_bid: 2 }
    }
    player {
        state { auction_pass_order: 2 }
    }
    player {
        cash: 3
        state { last_bid: 3 }
    } 
    player {
        state { auction_pass_order: 3 }
    } 
    order: 0
    order: 1
    order: 2
    order: 3
    order: 4
    current_order_index: 1
    phase: "auction"
    state { current_bid: 3 }
}
