#include <Arduino.h>
#include "Mode.h"
#include "ModeOne.h"
#include "ModeTwo.h"
#include "ButtonA.h"

// Start with ModeOne as the current mode
Mode* CurrentMode = &ModeOne;

void switchMode(Mode* newMode)
{
    CurrentMode->stop();
    CurrentMode = newMode;
    CurrentMode->start();
}

void setup()
{
    Serial.begin(115200);

    // initialize inputs
    ButtonA.begin();

    // initialize modes
    ModeOne.begin();
    ModeTwo.begin();

    // start the selected mode
    CurrentMode->start();

    Serial.println("setup end");
}

void loop()
{
    // update inputs
    ButtonA.update();

    // update current mode
    CurrentMode->update();

    // if mode is finished, switch to the other mode...
    if (CurrentMode->isFinished()) {
        Serial.println("Mode says it is done...");
        if (CurrentMode == &ModeOne) {
            switchMode(&ModeTwo);
        } else {
            switchMode(&ModeOne);
        }
    }
}

