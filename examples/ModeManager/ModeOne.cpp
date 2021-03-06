#include <Arduino.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include "ModeOne.h"
#include "Button.h"

// Our global instance of the mode...
ModeOne_ ModeOne;

ModeOne_::ModeOne_()
{
    // Do not put debug here as Mode objects are typically constructed before
    // setup() is run, and so the Serial interface is not ready - if you use it
    // the Arduino may hang.
    setUpdatePeriod(500);
}

void ModeOne_::modeStart()
{
    Serial.println("ModeOne::modeStart()");
}

void ModeOne_::modeStop()
{
    Serial.println("ModeOne::modeStop()");
}

void ModeOne_::modeUpdate()
{
    Serial.print("ModeOne::modeUpdate() Millis=0x");
    Serial.println(Millis(), HEX);
    if (Button.tapped()) {
        _state = Finished;
    }
}

