#include <Arduino.h>
#include <MutilaDebug.h>
#include <Heartbeat.h>
#include <Millis.h>

Heartbeat::Heartbeat(const uint8_t pin, const bool invertedLogic) :
    _mode(Heartbeat::Normal),
	_pin(pin),
    _invertedLogic(invertedLogic),
    _pinState(true),
    _lastStateFlip(0),
    _onTime(0),
    _offTime(0),
    _enabled(true)
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
        _onTime = NormalOnMs;
        _offTime = NormalOffMs;
		break;
	case Quick:
        _onTime = QuickOnMs;
        _offTime = QuickOffMs;
		break;
	case Quicker:
        _onTime = QuickerOnMs;
        _offTime = QuickerOffMs;
		break;
	case Slow:
        _onTime = SlowOnMs;
        _offTime = SlowOffMs;
		break;
	case Slower:
        _onTime = SlowerOnMs;
        _offTime = SlowerOffMs;
		break;
    case Off:
        _onTime = 0;
        _offTime = 1;
		break;
    case On:
        _onTime = 1;
        _offTime = 0;
		break;
    default:
        break;
	}

}

void Heartbeat::setMode(Heartbeat::Times times) {
    if (times.mode == Custom) {
        setCustomMode(times.onTime, times.offTime);
    } else {
        setMode(times.mode);
    }
}

void Heartbeat::setCustomMode(uint16_t onTime, uint16_t offTime)
{
    _onTime = onTime;
    _offTime = offTime;
    _mode = Custom;
}

void Heartbeat::update()
{
    if (!_enabled) {
        return;
    }
    millis_t wait = _pinState ? _onTime : _offTime;
    if (_onTime == 0) {
        if (_pinState) {
            updatePin(0);
        }
        return;
    } else if (_offTime == 0) {
        if (!_pinState) {
            updatePin(1);
        }
        return;
    } else if (MillisSince(_lastStateFlip) >= wait) {
        updatePin(!_pinState);
    }
}

void Heartbeat::updatePin(bool state)
{
    _pinState = state;
    digitalWrite(_pin, _invertedLogic ? !_pinState : _pinState);
    _lastStateFlip = Millis();
}

Heartbeat::Times Heartbeat::times()
{
    Times t;
    t.mode = _mode;
    t.onTime = _onTime;
    t.offTime = _offTime;
    return t;
}

void Heartbeat::setEnabled(bool on)
{
    _enabled = on;
    if (!_enabled) {
        updatePin(false);
    }
}

