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

bool AbstractDebouncedButton::pushed()
{
    bool r = _pushed;
    _pushed = false;
    return r;
}

uint32_t AbstractDebouncedButton::tapped()
{
    uint32_t r = _lastOnDuration;
    _lastOnDuration = 0;
    return r;
}

bool AbstractDebouncedButton::held(uint16_t ms)
{
    return (on() && MillisSince(_lastStateChange) > ms);
}

bool AbstractDebouncedButton::repeat(uint16_t initialMs, uint16_t repeatMs)
{
    uint32_t now = Millis();
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
    uint32_t now = Millis();
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

