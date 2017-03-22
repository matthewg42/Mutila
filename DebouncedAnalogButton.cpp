#include <Arduino.h>
#include "DebouncedAnalogButton.h"
#include "Millis.h"

DebouncedAnalogButton::DebouncedAnalogButton(uint8_t pin, bool pullup, uint16_t analogThreshold) :
    RawButton(pin, pullup),
    _analogThreshold(analogThreshold)
{
}

void DebouncedAnalogButton::begin(uint8_t threshold, uint8_t delay)
{
    // we don't need to call RawButton::begin() because analogRead 
    // deoesn't require that pinMode be called...
    _threshold = threshold;
    _delay = delay;
    _lastUpdate = 0;
    setState(false);
    _lastOnDuration = 0;
}

void DebouncedAnalogButton::update()
{
    if (Millis() > _lastUpdate + _delay) {
        if (_on() != _state) {
            _counter++;
            if (_counter > _threshold) {
                setState(!_state);
            }
        } else if (_counter > 0) {
            _counter = 0;
        }
        _lastUpdate = Millis();
    }
}

// over-rides RawButton::on
bool DebouncedAnalogButton::on()
{
    return _state;
}

bool DebouncedAnalogButton::pushed()
{
    bool r = _pushed;
    _pushed = false;
    return r;
}

unsigned long DebouncedAnalogButton::tapped()
{
    unsigned long r = _lastOnDuration;
    _lastOnDuration = 0;
    return r;
}

bool DebouncedAnalogButton::held(uint16_t ms)
{
    return (on() && Millis() > _lastStateChange + ms);
}

bool DebouncedAnalogButton::repeat(uint16_t initialMs, uint16_t repeatMs)
{
    bool r = on() && Millis() > _nextRepeatTime;
    if (r) {
        if (_repeatCount++ == 0) {
            _nextRepeatTime += initialMs;
        } else {
            _nextRepeatTime += repeatMs;
        }
    }
    return r;
}

void DebouncedAnalogButton::setState(bool newState)
{
    unsigned long now = Millis();
    if (newState) { 
        _pushed = true;
        _repeatCount = 0;
        _nextRepeatTime = now;
    } else {
        _lastOnDuration = now - _lastStateChange;
    }
    if (_state!=newState) {
        _lastStateChange = now;
        _state = newState;
        _counter = 0;
    }
}

bool DebouncedAnalogButton::_on()
{
    if (_pullup) {
        return analogRead(_pin) <= _analogThreshold;
    } else {
        return analogRead(_pin) > _analogThreshold;
    }
}

