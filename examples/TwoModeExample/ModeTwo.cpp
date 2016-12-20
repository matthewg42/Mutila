#include <Arduino.h>
#include "ModeTwo.h"
#include "ButtonA.h"

// Our global instance of the mode...
ModeTwo_ ModeTwo;

ModeTwo_::ModeTwo_()
{
    // Do not put debug here as Mode objects are typically constructed before
    // setup() is run, and so the Serial interface is not ready - if you use it
    // the Arduino may hang.
    setUpdatePeriod(500);
}

void ModeTwo_::modeStart()
{
    Serial.println(F("ModeTwo::modeStart()"));
}

void ModeTwo_::modeStop()
{
    Serial.println(F("ModeTwo::modeStop()"));
}

void ModeTwo_::modeUpdate()
{
    Serial.println(F("ModeTwo::modeUpdate() doing a thing..."));
}

bool ModeTwo_::isFinished()
{
    return ButtonA.tapped();
}

