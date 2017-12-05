#include <Arduino.h>
#include <MutilaDebug.h>
#include <ModeManager.h>
#include "ModeOne.h"
#include "ModeTwo.h"
#include "ButtonA.h"

ModeManagerClass ModeManager;

void setup()
{
    Serial.begin(115200);

    // initialize inputs
    ButtonA.begin();

    // initialize modes
    ModeOne.begin();
    ModeTwo.begin();

    // start the selected mode
    ModeManager.begin(&ModeOne);

    // test that everything works OK over Millis wrap
    addMillisOffset(0xFFFFF000);

    DBLN("setup() complete");
}

void loop()
{
    // update inputs
    ButtonA.update();
    ModeManager.update();

    if (ModeManager.modeFinished()) {
        DBLN("Mode says it is done...");
        if (ModeManager.currentMode == &ModeOne) {
            ModeManager.switchMode(&ModeTwo);
        } else {
            ModeManager.switchMode(&ModeOne);
        }
    }
}

