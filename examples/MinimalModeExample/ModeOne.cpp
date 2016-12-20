#include <Arduino.h>
#include "ModeOne.h"

ModeOne::ModeOne()
{
    // Do not put debug here as Mode objects are typically constructed before
    // setup() is run, and so the Serial interface is not ready - if you use it
    // the Arduino may hang.
}

void ModeOne::start()
{
    Serial.println(F("ModeOne::start()"));
    _last = millis();
}

void ModeOne::stop()
{
    Serial.println(F("ModeOne::stop()"));
}

void ModeOne::update()
{
    // Only do a thing is we haven't for 50 ms
    if (millis() - _last > 500) {
        _last = millis();
        Serial.println(F("ModeOne::update() doing a thing..."));
    }
}

