game {
  player {
    state {
      queued_build {
        build_in {
          location {
            row: 1
            col: 2
          }
        }
      }
    }
    cash: 10
    power: POWER_URBANIZATION
    color: COLOR_BLUE
  }
  order: 0
  current_order_index: 0
  phase: PHASE_BUILD
  map {
    row {
      hex {
      }
      hex {
        track {
          from {
            row: 1
            col: 0
          }
          to {
            row: 0
            col: 0
          }
          owner_index: 0
        }
      }
      hex {
      }
      hex {
      }
      hex {
      }
    }
    row {
      hex {
        city_index: 0
      }
      hex {
        track {
          from {
            row: 1
            col: 0
          }
          to {
            row: 1
            col: 2
          }
          owner_index: 0
        }
      }
      hex {
        has_town: true
      }
      hex {
      }
      hex {
      }
    }
    row {
      hex {
      }
      hex {
        track {
          from {
            row: 1
            col: 0
          }
          to {
            row: 2
            col: 0
          }
          owner_index: 0
        }
      }
      hex {
      }
      hex {
      }
      hex {
      }
    }
  }
  terrain {
    build_cost: 2
  }
  city {
  }
}
expected_options {
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 2
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 2
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 2
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 2
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 2
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 2
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 2
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 2
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 2
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 0
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 1
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 1
          col: 3
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 1
          col: 2
        }
        to {
          row: 2
          col: 3
        }
        owner_index: 0
      }
    }
  }
  action {
    build_undo: true
  }
}
selected_action: 0
result {
  player {
    state {
      queued_build {
        build_in {
          location {
            row: 1
            col: 2
          }
          track {
            from {
              row: 1
              col: 2
            }
            to {
              row: 1
              col: 1
            }
            owner_index: 0
          }
        }
      }
    }
    cash: 10
    power: POWER_URBANIZATION
    color: COLOR_BLUE
  }
  order: 0
  current_order_index: 0
  phase: PHASE_BUILD
  map {
    row {
      hex {
      }
      hex {
        track {
          from {
            row: 1
            col: 0
          }
          to {
            row: 0
            col: 0
          }
          owner_index: 0
        }
      }
      hex {
      }
      hex {
      }
      hex {
      }
    }
    row {
      hex {
        city_index: 0
      }
      hex {
        track {
          from {
            row: 1
            col: 0
          }
          to {
            row: 1
            col: 2
          }
          owner_index: 0
        }
      }
      hex {
        has_town: true
      }
      hex {
      }
      hex {
      }
    }
    row {
      hex {
      }
      hex {
        track {
          from {
            row: 1
            col: 0
          }
          to {
            row: 2
            col: 0
          }
          owner_index: 0
        }
      }
      hex {
      }
      hex {
      }
      hex {
      }
    }
  }
  terrain {
    build_cost: 2
  }
  city {
  }
}
