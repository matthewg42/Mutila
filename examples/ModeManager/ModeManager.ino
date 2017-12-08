#include <Arduino.h>
#include <MutilaDebug.h>
#include <ModeManager.h>
#include "ModeOne.h"
#include "ModeTwo.h"
#include "Button.h"

ModeManager Modes;

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // show that we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    // initialize inputs
    Button.begin();

    // initialize modes
    ModeOne.begin();
    ModeTwo.begin();

    // start the selected mode
    Modes.begin(&ModeOne);

    Serial.println("setup() end");
}

void loop()
{
    // update inputs
    Button.update();
    Modes.update();

    if (Modes.modeFinished()) {
        Serial.println("Mode says it is done...");
        if (Modes.currentMode == &ModeOne) {
            Modes.switchMode(&ModeTwo);
        } else {
            Modes.switchMode(&ModeOne);
        }
    }
}

