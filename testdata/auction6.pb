game {
    player {
        cash: 5
        state { last_bid: 3 }
    }
    player {
    }
    player {
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
    phase: "auction"
    state { current_bid: 10 }
}
expected_options {
    action { bid { pass: true } }
}
selected_action: 0
result {
    player {
        cash: 5
        state { auction_pass_order: 1 last_bid: 3 }
    }
    player {
    }
    player {
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
    current_order_index: 1
    phase: "auction"
    state { current_bid: 10 }
}
