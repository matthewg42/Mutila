#include <Arduino.h>
#include <MutilaDebug.h>
#include "Mode.h"
#include "ModeA.h"
#include "ModeB.h"
#include "ButtonA.h"
#include "ButtonB.h"

/*
 * ParentMode example
 * ==================
 *
 * Here we have two top-level modes which are controlled by ButtonA
 * (see Config.h for button pins). The two modes are:
 * 
 * ModeA - a ParentMode with two child modes ModeA1 and ModeA2
 * ModeB - a regular Mode, ModeB
 *
 * All the "leaf" Modes (ModeA1, ModeA2 and ModeB) simply maintain a 
 * counter and increment it every 500ms or so, printing a message to
 * describe their current state.
 *
 * ModeA is the focus of this example - it monitors ButtonB and 
 * switches it's active child Mode between ModeA1 and ModeA2 when it
 * sees that the button has been pressed.
 *
 * Arbitrarily complex trees of modes may be created, but there are 
 * some caveats:
 *
 * 1. Memory usage. Modes take RAM. Arduino's don't have much RAM
 * 2. Testing DebouncedButton.tapped() resets it's state, so you
 *    probably don't want a button checked at multiple levels in
 *    a Mode tree!
 *
 */

// The top level mode (which ParentMode, ModeA or ModeB is active)
Mode* TopMode = NULL;

void switchMode(Mode* newMode)
{
    // only switch modes if the newMode is different from the
    // current mode
    if (TopMode != newMode) {
        // only call stop() of we have an actual mode to stop
        if (TopMode != NULL) {
            TopMode->stop();
        }
        TopMode = newMode;
        TopMode->start();
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.println(F("setup() start"));

    // Show that we can handle Millis overflow
    addMillisOffset(0xFFFFF000);

    // Initialize top level modes. It is customary for top level 
    // ParentModes to call begin() for child modes which they 
    // manage. 
    ModeA.begin();
    ModeB.begin();

    // Initialize buttons
    ButtonA.begin();
    ButtonB.begin();

    // Arbitrarily decide we're in ModeA to start with
    switchMode(&ModeA);

    Serial.println(F("setup() end"));
}

void loop()
{
    // Give a timeslice to out various components
    ButtonA.update();
    ButtonB.update();
    TopMode->update();

    // Which top level mode is active depents on the state of ButtonA
    if (ButtonA.tapped()) {
        if (TopMode == &ModeA) {
            switchMode(&ModeB);
        } else {
            switchMode(&ModeA);
        }
    }
}

