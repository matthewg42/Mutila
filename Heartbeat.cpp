#include <Arduino.h>
#include "Mutila.h"
#include "Heartbeat.h"

Heartbeat::Heartbeat(int pin) :
    _mode(Heartbeat::Normal),
	_pin(pin),
    _pinState(true),
    _lastStateFlip(0),
    _onTime(0),
    _offTime(0)
{
	setMode(_mode);
}

Heartbeat::~Heartbeat()
{
}

void Heartbeat::begin()
{
    pinMode(_pin, OUTPUT);
}

Heartbeat::Mode Heartbeat::mode()
{
    return _mode;
}

void Heartbeat::setMode(Mode mode)
{
	_mode = mode;
	switch (_mode) {
	case Normal:
        _onTime = HEARTBEAT_NORMAL_ON_MS;
        _offTime = HEARTBEAT_NORMAL_OFF_MS;
		break;
	case Quick:
        _onTime = HEARTBEAT_QUICK_ON_MS;
        _offTime = HEARTBEAT_QUICK_OFF_MS;
		break;
	case Slow:
        _onTime = HEARTBEAT_SLOW_ON_MS;
        _offTime = HEARTBEAT_SLOW_OFF_MS;
		break;
	case Slower:
        _onTime = HEARTBEAT_SLOW_ON_MSER;
        _offTime = HEARTBEAT_SLOW_OFF_MSER;
		break;
	}
}

void Heartbeat::update()
{
    unsigned long wait = _pinState ? _onTime : _offTime;
    if (millis() - _lastStateFlip >= wait) {
        updatePin(!_pinState);
    }
}

void Heartbeat::updatePin(bool state)
{
    _pinState = state;
    digitalWrite(_pin, _pinState);
    _lastStateFlip = millis();
}


