#include <Arduino.h>
#include "DebouncedAnalogButton.h"
#include "Millis.h"

DebouncedAnalogButton::DebouncedAnalogButton(const uint8_t pin, const bool pullup, const uint16_t analogThreshold) :
    AnalogButton(pin, pullup, analogThreshold)
{
}

void DebouncedAnalogButton::begin(uint8_t threshold, uint8_t delay)
{
    AbstractDebouncedButton::begin(threshold, delay);
    AnalogButton::begin();
}

void DebouncedAnalogButton::update()
{
    if (DoEvery(_delay, _lastUpdate)) {
        if (AnalogButton::on() != _state) {
            _counter++;
            if (_counter > _threshold) {
                setState(!_state);
            }
        } else if (_counter > 0) {
            _counter = 0;
        }
    }
}

// over-rides DigitalButton::on
bool DebouncedAnalogButton::on()
{
    return _state;
}

