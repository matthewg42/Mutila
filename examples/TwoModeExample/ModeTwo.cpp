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
}

void ModeTwo_::start()
{
    Serial.println(F("ModeTwo::start()"));
    _last = millis();
    _start = _last;
}

void ModeTwo_::stop()
{
    Serial.println(F("ModeTwo::stop()"));
}

void ModeTwo_::update()
{
    // Only do a thing is we haven't for 50 ms
    if (millis() - _last > 500) {
        _last = millis();
        Serial.println(F("ModeTwo::update() doing a thing..."));
    }
}

bool ModeTwo_::isFinished()
{
    return ButtonA.tapped();
}

