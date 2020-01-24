#include <stdlib.h>
#include <Arduino.h>
#include <Millis.h>
#include <QuantizedPot.h>

QuantizedPot::QuantizedPot(const uint8_t pin, int8_t maxRanges) :
    _pin(pin),
	_rangeMax(maxRanges),
	_rangeCount(0)
{
	// allocate ptr array for ranges
	_ranges = new NumericRange<int>*[maxRanges];

	// set them all to NULL for now
	for (int8_t i=0; i<_rangeMax; i++) {
		_ranges[i] = NULL;
	}
	
}

QuantizedPot::~QuantizedPot()
{
	if (_ranges != NULL) {
		for (int8_t i=0; i<_rangeMax; i++) {
			if (_ranges[i] != NULL) {
				delete _ranges[i];
				_ranges[i] = NULL;
			}
		}
		delete _ranges;
		_ranges = NULL;
	}
}

int8_t QuantizedPot::addRange(int start, int end)
{
	if (_rangeCount >= _rangeMax) {
		return -1;
	}

	if (_ranges[_rangeCount] != NULL) {
		delete _ranges[_rangeCount];
	}

	_ranges[_rangeCount] = new NumericRange<int>(start, end);
	return _rangeCount++;
}

void QuantizedPot::begin(uint8_t threshold, uint8_t delay)
{
    _threshold = threshold;
    _delay = delay;
	_lastRaw = 0;
    setState(0);
}

void QuantizedPot::update()
{
    if (DoEvery(_delay, _lastUpdate)) {
        int8_t valueNow = _value();
        if (valueNow != _state) {
            _counter++;
            if (_counter > _threshold) {
                setState(valueNow);
            } 
        } else if (_counter > 0) {
            _counter = 0;
        }
    }
}

int8_t QuantizedPot::value()
{
    return _state;
}

int8_t QuantizedPot::_value()
{
    // 0 <= raw < 1024
    int raw = analogRead(_pin);
	_velocity = raw - _lastRaw;
	_lastRaw = raw;
	for (int8_t i=0; i<_rangeCount; i++) {
		if (_ranges[i]->contains(raw)) {
			return i;
		}
	}
	return -1;
}

void QuantizedPot::setState(int8_t newState)
{
    _lastStateChange = Millis();
    _state = newState;
    _counter = 0;
}

