#include <Arduino.h>
#include "DigitalButton.h"

DigitalButton::DigitalButton(const uint8_t pin, const bool pullup) : 
    _pin(pin),
    _pullup(pullup)
{
}

void DigitalButton::begin()
{
    if (_pullup) {
        pinMode(_pin, INPUT_PULLUP);
    } else {
        pinMode(_pin, INPUT);
    }
}

bool DigitalButton::on()
{
    if (_pullup) {
        return !digitalRead(_pin);
    } else {
        return digitalRead(_pin);
    }
}

