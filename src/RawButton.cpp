#include <Arduino.h>
#include "RawButton.h"

RawButton::RawButton(const uint8_t pin, const bool pullup) : 
    _pin(pin),
    _pullup(pullup)
{
}

void RawButton::begin()
{
    if (_pullup) {
        pinMode(_pin, INPUT_PULLUP);
    } else {
        pinMode(_pin, INPUT);
    }
}

bool RawButton::on()
{
    if (_pullup) {
        return !digitalRead(_pin);
    } else {
        return digitalRead(_pin);
    }
}

