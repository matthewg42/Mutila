#include <Arduino.h>
#include <MutilaDebug.h>
#include "MyBrownoutMode.h"

MyBrownoutMode::MyBrownoutMode(EMAVDivSampler& vSampler, const float vThreshLow, const float vThreshHigh) : 
    BrownoutMode(vSampler, vThreshLow, vThreshHigh)
{
    // Do not put debug here as Mode objects are typically constructed before
    // setup() is run, and so the Serial interface is not ready - if you use it
    // the Arduino may hang.

    setUpdatePeriod(500);
}

void MyBrownoutMode::enterBrownout()
{
    // Typical use: save state to EEPROM etc...
    DBLN(F("MyBrownoutMode::enterBrownout()"));
}

void MyBrownoutMode::exitBrownout()
{
    // Typical use: restore state from EEPROM
    DBLN(F("MyBrownoutMode::exitBrownout()"));
}

void MyBrownoutMode::modeUpdate()
{
    DB(F("MyBrownoutMode::modeUpdate() volts="));
    DBLN(_vSampler.averageVolts());
}

