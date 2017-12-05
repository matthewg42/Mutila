#include <Arduino.h>
#include "AnalogButton.h"

AnalogButton::AnalogButton(const uint8_t pin, const uint16_t analogThreshold, const bool invert) : 
    _pin(pin),
    _analogThreshold(analogThreshold),
    _invert(invert)
{
}

void AnalogButton::begin()
{
    // analog inputs don't need to have their mode set explicitly
}

bool AnalogButton::on()
{
    if (_invert) {
        return (uint16_t)analogRead(_pin) <= _analogThreshold;
    } else {
        return (uint16_t)analogRead(_pin) > _analogThreshold;
    }
}

