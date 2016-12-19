#include <Arduino.h>
#include "DebouncedButton.h"

DebouncedButton::DebouncedButton(uint8_t pin, bool pullup) :
    RawButton(pin, pullup)
{
}

void DebouncedButton::begin(uint8_t threshold, uint8_t delay)
{
    RawButton::begin();
    _threshold = threshold;
    _delay = delay;
    _lastUpdate = 0;
    setState(false);
    _released = false; // prevent false positive on startup
}

void DebouncedButton::update()
{
    if (millis() > _lastUpdate + _delay) {
        if (RawButton::on() != _state) {
            _counter++;
            if (_counter > _threshold) {
                setState(!_state);
            }
        } else if (_counter > 0) {
            _counter = 0;
        }
        _lastUpdate = millis();
    }
}

// over-rides RawButton::on
bool DebouncedButton::on()
{
    return _state;
}

bool DebouncedButton::pushed()
{
    bool r = _pushed;
    _pushed = false;
    return r;
}

bool DebouncedButton::tapped()
{
    bool r = _released;
    _released = false;
    return r;
}

bool DebouncedButton::held(uint16_t ms)
{
    return (on() && millis() > _lastStateChange + ms);
}

bool DebouncedButton::repeat(uint16_t initialMs, uint16_t repeatMs)
{
    bool r = on() && millis() > _nextRepeatTime;
    if (r) {
        if (_repeatCount++ == 0) {
            _nextRepeatTime += initialMs;
        } else {
            _nextRepeatTime += repeatMs;
        }
    }
    return r;
}

void DebouncedButton::setState(bool newState)
{
    if (newState) { 
        _pushed = true;
        _repeatCount = 0;
        _nextRepeatTime = millis();
    } else {
        _released = true;
    }
    if (_state!=newState) {
        _lastStateChange = millis();
        _state = newState;
        _counter = 0;
    }
}

