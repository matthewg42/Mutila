#include <Arduino.h>
#include <AnalogInputButton.h>

AnalogInputButton::AnalogInputButton(const uint8_t pin, const bool pullup, const uint16_t analogThreshold) : 
    _pin(pin),
    _pullup(pullup),
    _analogThreshold(analogThreshold)
{
}

void AnalogInputButton::begin()
{
    // analog inputs don't need to have their mode set explicitly
}

bool AnalogInputButton::on()
{
    if (_pullup) {
        return (uint16_t)analogRead(_pin) <= _analogThreshold;
    } else {
        return (uint16_t)analogRead(_pin) > _analogThreshold;
    }
}

