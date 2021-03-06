#include <Arduino.h>
#include <MutilaDebug.h>
#include "ModeTwo.h"
#include "Button.h"

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
    Serial.println("ModeTwo::modeStart()");
}

void ModeTwo_::modeStop()
{
    Serial.println("ModeTwo::modeStop()");
}

void ModeTwo_::modeUpdate()
{
    Serial.print("ModeTwo::modeUpdate() Millis=0x");
    Serial.println(Millis(), HEX);
}

bool ModeTwo_::isFinished()
{
    return Button.tapped();
}

