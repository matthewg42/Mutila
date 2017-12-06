#include <Arduino.h>
#include "DualInputButton.h"

DualInputButton::DualInputButton(AbstractButton& button1, AbstractButton& button2) :
    _button1(button1),
    _button2(button2)
{
}

void DualInputButton::begin(bool callBeginInChildren)
{
    if (callBeginInChildren) {
        _button1.begin();
        _button2.begin();
    }
}

bool DualInputButton::on()
{
    return _button1.on() || _button2.on();
}

