#include <Arduino.h>
#include "DigitalInputButton.h"

DigitalInputButton::DigitalInputButton(const uint8_t pin, const bool pullup) : 
    _pin(pin),
    _pullup(pullup)
{
}

void DigitalInputButton::begin()
{
    if (_pullup) {
        pinMode(_pin, INPUT_PULLUP);
    } else {
        pinMode(_pin, INPUT);
    }
}

bool DigitalInputButton::on()
{
    if (_pullup) {
        return !digitalRead(_pin);
    } else {
        return digitalRead(_pin);
    }
}

