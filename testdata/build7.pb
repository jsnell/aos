game {
  player {
    state {
      queued_build {
        build_in {
          location {
            row: 1
            col: 1
          }
        }
      }
    }
    cash: 10
    color: COLOR_RED
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
        city_index: 0
      }
    }
    row {
      hex {
      }
      hex {
      }
      hex {
        track {
          from {
            row: 0
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
}
expected_options {
  action {
    build_in {
      location {
        row: 1
        col: 1
      }
      track {
        from {
          row: 0
          col: 1
        }
        to {
          row: 0
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
        col: 1
      }
      track {
        from {
          row: 0
          col: 1
        }
        to {
          row: 1
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
        col: 1
      }
      track {
        from {
          row: 0
          col: 2
        }
        to {
          row: 1
          col: 0
        }
        owner_index: 0
      }
    }
  }
  action {
    build_in {
      location {
        row: 1
        col: 1
      }
      track {
        from {
          row: 0
          col: 2
        }
        to {
          row: 1
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
        col: 1
      }
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
  }
  action {
    build_in {
      location {
        row: 1
        col: 1
      }
      track {
        from {
          row: 0
          col: 1
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
          col: 0
        }
        to {
          row: 1
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
        col: 1
      }
      track {
        from {
          row: 0
          col: 1
        }
        to {
          row: 1
          col: 2
        }
        owner_index: 0
      }
      track {
        from {
          row: 0
          col: 2
        }
        to {
          row: 1
          col: 0
        }
        owner_index: 0
      }
    }
  }
  action {
    build_undo: true
  }
}
