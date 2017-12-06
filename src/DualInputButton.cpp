#include <Arduino.h>
#include "DualInputButton.h"

DualInputButton::DualInputButton(AbstractButton& button1, AbstractButton& button2, const MixMode mix) :
    _button1(button1),
    _button2(button2),
    _mix(mix)
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
    switch (_mix) {
    case Or:
        return _button1.on() || _button2.on();
        break;
    case Xor:
        return _button1.on() ^ _button2.on();
        break;
    case And:
        return _button1.on() && _button2.on();
        break;
    }
}

