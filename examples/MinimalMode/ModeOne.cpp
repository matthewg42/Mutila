#include <Arduino.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include "ModeOne.h"

ModeOne::ModeOne() 
{
    // Do not put debug here as Mode objects are typically constructed before
    // setup() is run, and so the Serial interface is not ready - if you use it
    // the Arduino may hang.

    // modeUpdate() will only be called every 500 ms...
    setUpdatePeriod(500);
}

void ModeOne::modeUpdate()
{
    Serial.print("ModeOne::modeUpdate() Millis=0x");
    Serial.println(Millis(), HEX);
}

