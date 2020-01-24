#include <Arduino.h>
#include "AbstractDebouncedButton.h"
#include "MutilaDebug.h"
#include "Millis.h"

AbstractDebouncedButton::AbstractDebouncedButton() 
{
}

void AbstractDebouncedButton::begin(uint8_t threshold, uint8_t delay)
{
    _threshold = threshold;
    _delay = delay;
    _lastUpdate = 0;
    _lastRepeat = 0;
    setState(false);
    _lastOnDuration = 0;
}

bool AbstractDebouncedButton::pushed(bool peek)
{
    bool r = _pushed;
    if (!peek) { _pushed = false; }
    return r;
}

millis_t AbstractDebouncedButton::tapped(bool peek)
{
    millis_t r = _lastOnDuration;
    if (!peek) { _lastOnDuration = 0; }
    return r;
}

bool AbstractDebouncedButton::held(uint16_t ms)
{
    return (on() && MillisSince(_lastStateChange) > ms);
}

bool AbstractDebouncedButton::repeat(uint16_t initialMs, uint16_t repeatMs)
{
    millis_t now = Millis();
    bool out = false;

    if (on() && _repeatCount == 0) {
        out = true;
    } else if (on() && MillisSince(_lastRepeat, now) > (_repeatCount == 1 ? initialMs : repeatMs)) {
        out = true;
    }

    if (out) {
        _lastRepeat = now;
        _repeatCount++;
    }

    return out;
}

void AbstractDebouncedButton::setState(bool newState)
{
    millis_t now = Millis();
    if (newState) { 
        _pushed = true;
        _repeatCount = 0;
        _lastRepeat = now;
    } else {
        _lastOnDuration = MillisSince(_lastStateChange, now);
    }
    if (_state!=newState) {
        _lastStateChange = now;
        _state = newState;
        _counter = 0;
    }
}

