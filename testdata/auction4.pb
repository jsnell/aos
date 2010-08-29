game {
    player {
        name: "Andy"
        loans: 4
        cash: 3
        state { last_bid: 2 }
    }
    player {
        name: "Beth"
        loans: 3
        cash: 2
    }
    order: 0
    order: 1
    current_order_index: 0
    phase: "auction"
    state { current_bid: 2 }
}
expected_options {
    action { bid { pass: true } }
    action { bid { amount: 2 } }
    action { bid { amount: 3 } }
}
selected_action: 1
result {
    player {
        name: "Andy"
        loans: 4
        cash: 3
        state { last_bid: 2 }
    }
    player {
        name: "Beth"
        loans: 3
        cash: 2
    }
    order: 0
    order: 1
    current_order_index: 1
    phase: "auction"
    state { current_bid: 2 }
}
