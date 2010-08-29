game {
    player {
        name: "Andy"
        loans: 4
        cash: 8
        state { last_bid: 2 }
    }
    player {
        name: "Beth"
        loans: 3
        cash: 2
        state { auction_pass_order: 1 }
    }
    order: 0
    order: 1
    current_order_index: 0
    phase: "auction"
    state { current_bid: 2 }
}
expected_options {
    action { bid { pass: true } }
}
selected_action: 0
result {
    player {
        name: "Andy"
        loans: 4
        cash: 6
        state { auction_pass_order: 2 last_bid: 2 }
    }
    player {
        name: "Beth"
        loans: 3
        cash: 2
        state { auction_pass_order: 1 }
    }
    order: 0
    order: 1
    current_order_index: 0
    phase: "power"
    state { current_bid: 2 }
}
