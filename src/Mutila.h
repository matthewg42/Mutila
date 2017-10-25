#pragma once

//! Raise this to make anti-bounce "harder".
#define DEBOUNCED_BUTTON_THRESHOLD      5

//! Raise this to poll less frequently.
#define DEBOUNCED_BUTTON_DELAY          5

//! How long before we consider the button held.
#define DEBOUNCED_BUTTON_HELD_MS        800

//! Initial time between press and first repeat in ms.
#define DEBOUNCED_BUTTON_RPT_INITIAL_MS 700

//! Time between subsequent repeats in ms.
#define DEBOUNCED_BUTTON_RPT_MS         350


// Heartbeat class
#define HEARTBEAT_NORMAL_ON_MS          50
#define HEARTBEAT_NORMAL_OFF_MS         450
#define HEARTBEAT_QUICK_ON_MS           25
#define HEARTBEAT_QUICK_OFF_MS          125
#define HEARTBEAT_QUICKER_ON_MS         25
#define HEARTBEAT_QUICKER_OFF_MS        25
#define HEARTBEAT_SLOW_ON_MS            50
#define HEARTBEAT_SLOW_OFF_MS           950
#define HEARTBEAT_SLOWER_ON_MS          50
#define HEARTBEAT_SLOWER_OFF_MS         1950


