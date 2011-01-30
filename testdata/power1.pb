game {
    player {
      power: POWER_FIRST_MOVE
    }
    player {
    }
    order: 0
    order: 1
    current_order_index: 1
    phase: PHASE_TAKE_POWERS
    power: POWER_LOCOMOTIVE
    power: POWER_PRODUCTION
    power: POWER_FIRST_MOVE
}
expected_options {
  action { take_power { power: POWER_LOCOMOTIVE } }
  action { take_power { power: POWER_PRODUCTION } }
}
selected_action: 0
result {
    player {
      power: POWER_FIRST_MOVE
    }
    player {
      power: POWER_LOCOMOTIVE
      link_level: 2
    }
    order: 0
    order: 1
    current_order_index: 0
    phase: PHASE_BUILD
    power: POWER_LOCOMOTIVE
    power: POWER_PRODUCTION
    power: POWER_FIRST_MOVE
}
