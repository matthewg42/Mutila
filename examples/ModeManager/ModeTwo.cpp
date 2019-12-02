#include <Arduino.h>
#include <MutilaDebug.h>
#include "ModeTwo.h"
#include "Button.h"

// Our global instance of the mode...
ModeTwoClass ModeTwo;

ModeTwoClass::ModeTwoClass()
{
    // Do not put debug here as Mode objects are typically constructed before
    // setup() is run, and so the Serial interface is not ready - if you use it
    // the Arduino may hang.
    setUpdatePeriod(500);
}

void ModeTwoClass::modeStart()
{
    Serial.println("ModeTwo::modeStart()");
}

void ModeTwoClass::modeStop()
{
    Serial.println("ModeTwo::modeStop()");
}

void ModeTwoClass::modeUpdate()
{
    Serial.print("ModeTwo::modeUpdate() Millis=0x");
    Serial.println(Millis(), HEX);
}

bool ModeTwoClass::isFinished()
{
    return Button.tapped();
}

