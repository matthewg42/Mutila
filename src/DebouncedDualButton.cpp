#include <Arduino.h>
#include "DebouncedDualButton.h"
#include "MutilaDebug.h"
#include "Millis.h"

DebouncedDualButton::DebouncedDualButton(AbstractButton& button1, AbstractButton& button2) :
    DualInputButton(button1, button2)
{
}

void DebouncedDualButton::begin(bool callBeginInChildren, uint8_t threshold, uint8_t delay)
{
    AbstractDebouncedButton::begin(threshold, delay);
    DualInputButton::begin(callBeginInChildren);
}

void DebouncedDualButton::update()
{
    if (DoEvery(_delay, _lastUpdate)) {
        if (DualInputButton::on() != _state) {
            _counter++;
            if (_counter > _threshold) {
                setState(!_state);
            }
        } else if (_counter > 0) {
            _counter = 0;
        }
    }
}

bool DebouncedDualButton::on()
{
    return _state;
}

