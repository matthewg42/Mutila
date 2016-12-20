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

    // Settle down
    delay(300);

    Serial.println("setup end");
}

void loop()
{
    // update inputs
    ButtonA.update();

    // update current mode
    CurrentMode->update();
    if (CurrentMode->isFinished()) {
        Serial.println("CurrentMode said it was done...");
        if (CurrentMode == &ModeOne) {
            switchMode(&ModeTwo);
        } else {
            switchMode(&ModeOne);
        }
    }
}

