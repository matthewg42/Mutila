#include <Arduino.h>
#include "DebouncedButton.h"
#include "MutilaDebug.h"
#include "Millis.h"

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
    _lastRepeat = 0;
    setState(false);
    _lastOnDuration = 0;
}

void DebouncedButton::update()
{
    //TODO: remove
    //if (Millis() > _lastUpdate + _delay) {
    if (MillisSince(_lastUpdate) > _delay) {
        _lastUpdate = Millis();
        if (RawButton::on() != _state) {
            _counter++;
            if (_counter > _threshold) {
                setState(!_state);
            }
        } else if (_counter > 0) {
            _counter = 0;
        }
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

uint32_t DebouncedButton::tapped()
{
    uint32_t r = _lastOnDuration;
    _lastOnDuration = 0;
    return r;
}

bool DebouncedButton::held(uint16_t ms)
{
    //TODO: remove
    //return (on() && Millis() > _lastStateChange + ms);
    return (on() && MillisSince(_lastStateChange) > ms);
}

bool DebouncedButton::repeat(uint16_t initialMs, uint16_t repeatMs)
{
    //TODO: remove
    //bool r = on() && Millis() > _nextRepeatTime;
    //if (r) {
    //    if (_repeatCount++ == 0) {
    //        _nextRepeatTime += initialMs;
    //    } else {
    //        _nextRepeatTime += repeatMs;
    //    }
    //}

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

void DebouncedButton::setState(bool newState)
{
    uint32_t now = Millis();
    if (newState) { 
        _pushed = true;
        _repeatCount = 0;
        // TODO remove 
        // _nextRepeatTime = now;
        _lastRepeat = now;
    } else {
        //TODO remove 
        //_lastOnDuration = now - _lastStateChange;
        _lastOnDuration = MillisSince(_lastStateChange, now);
    }
    if (_state!=newState) {
        _lastStateChange = now;
        _state = newState;
        _counter = 0;
    }
}

