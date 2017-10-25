#include "ToggleButton.h"

ToggleButton::ToggleButton(uint8_t pin, bool pullup) :
    _button(pin, pullup)
{
}

void ToggleButton::begin(bool startState, uint8_t threshold, uint8_t delay)
{
    _toggled = startState;
    _button.begin(threshold, delay);
}

void ToggleButton::update()
{
    _button.update();
    if (_button.pushed()) {
        _toggled = !_toggled;
    }
}

bool ToggleButton::on()
{
    return _toggled;
}


