#include <Arduino.h>
#include <MutilaDebug.h>
#include <ModeManager.h>
#include "ModeOne.h"
#include "ModeTwo.h"
#include "ButtonA.h"

ModeManager Modes;

void setup()
{
    Serial.begin(115200);

    // initialize inputs
    ButtonA.begin();

    // initialize modes
    ModeOne.begin();
    ModeTwo.begin();

    // start the selected mode
    Modes.begin(&ModeOne);

    // test that everything works OK over Millis wrap
    addMillisOffset(0xFFFFF000);

    DBLN("setup() complete");
}

void loop()
{
    // update inputs
    ButtonA.update();
    Modes.update();

    if (Modes.modeFinished()) {
        DBLN("Mode says it is done...");
        if (Modes.currentMode == &ModeOne) {
            Modes.switchMode(&ModeTwo);
        } else {
            Modes.switchMode(&ModeOne);
        }
    }
}

