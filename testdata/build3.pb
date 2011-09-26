game {
  player {
    cash: 10
  }
  order: 0
  current_order_index: 0
  phase: PHASE_BUILD
  map {
    row {
      hex {
      }
      hex {
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
      }
      hex {
      }
      hex {
        city_index: 0
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
}
expected_options {
  action {
    build_in {
      location {
        row: 0
        col: 2
      }
    }
  }
  action {
    build_in {
      location {
        row: 0
        col: 3
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 1
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 3
      }
    }
  }
  action {
    build_in {
      location {
        row: 2
        col: 2
      }
    }
  }
  action {
    build_in {
      location {
        row: 2
        col: 3
      }
    }
  }
  action {
    build_finish: true
  }
}
