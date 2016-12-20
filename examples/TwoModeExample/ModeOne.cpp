#include <Arduino.h>
#include "ModeOne.h"
#include "ButtonA.h"

// Our global instance of the mode...
ModeOne_ ModeOne;

ModeOne_::ModeOne_()
{
    // Do not put debug here as Mode objects are typically constructed before
    // setup() is run, and so the Serial interface is not ready - if you use it
    // the Arduino may hang.
}

void ModeOne_::start()
{
    Serial.println(F("ModeOne::start()"));
    _last = millis();
}

void ModeOne_::stop()
{
    Serial.println(F("ModeOne::stop()"));
}

void ModeOne_::update()
{
    // Only do a thing is we haven't for 50 ms
    if (millis() - _last > 500) {
        _last = millis();
        Serial.println(F("ModeOne::update() doing a thing..."));
    }
}

bool ModeOne_::isFinished()
{
    return ButtonA.tapped();
}

