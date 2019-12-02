#include <Arduino.h>
#include <MutilaDebug.h>
#include "ModeA.h"
#include "ModeA1.h"
#include "ModeA2.h"
#include "ButtonB.h"

// Our global instance of the mode...
ModeAClass ModeA;

ModeAClass::ModeAClass()
{
}

void ModeAClass::begin()
{
    Serial.println("ModeA::begin");
    // Initalize child modes which are managed by this ParentMode
    ModeA1.begin();
    ModeA2.begin();

    // And set which mode we start with (if any)
    switchMode(&ModeA1);
}

void ModeAClass::modeStart()
{
    Serial.println("ModeA::modeStart");
}

void ModeAClass::modeStop()
{
    Serial.println("ModeA::modeStop");
}

void ModeAClass::modeUpdate()
{
    // Update the currently active child mode
    if (pMode) { pMode->update(); }

    // And the rest of what this mode does is to decide when to switch
    // between the two child modes... which we'll do by looking at the
    // state of ButtonB - when it is tapped, switch child mode.
    if (ButtonB.tapped()) {
        if (pMode == &ModeA1) {
            switchMode(&ModeA2);
        } else {
            switchMode(&ModeA1);
        }
    }
}


