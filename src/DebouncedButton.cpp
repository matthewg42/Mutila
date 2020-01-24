#include <Arduino.h>
#include <DebouncedButton.h>
#include <MutilaDebug.h>
#include <Millis.h>

DebouncedButton::DebouncedButton(uint8_t pin, bool pullup) :
    DigitalInputButton(pin, pullup)
{
}

void DebouncedButton::begin(uint8_t threshold, uint8_t delay)
{
    AbstractDebouncedButton::begin(threshold, delay);
    DigitalInputButton::begin();
}

void DebouncedButton::update()
{
    if (DoEvery(_delay, _lastUpdate)) {
        if (DigitalInputButton::on() != _state) {
            _counter++;
            if (_counter > _threshold) {
                setState(!_state);
            }
        } else if (_counter > 0) {
            _counter = 0;
        }
    }
}

bool DebouncedButton::on()
{
    return _state;
}

