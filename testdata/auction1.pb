game {
    player {
        name: "Andy"
        loans: 4
        cash: 8
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
}
expected_options {
    action { bid { pass: true } }
    action { bid { amount: 1 } }
    action { bid { amount: 2 } }
    action { bid { amount: 3 } }
    action { bid { amount: 4 } }
    action { bid { amount: 5 } }
    action { bid { amount: 6 } }
    action { bid { amount: 7 } }
    action { bid { amount: 8 } }
}
selected_action: 2
result {
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
    }
    order: 0
    order: 1
    current_order_index: 1
    phase: "auction"
    state { current_bid: 2 }
}
