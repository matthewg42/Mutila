#include <Arduino.h>
#include "DiscretePot.h"
#include "Mutila.h"
#include "Millis.h"

DiscretePot::DiscretePot(uint8_t pin) :
    _pin(pin)
{
}

void DiscretePot::begin(int8_t min, int8_t max, bool reversed, uint8_t threshold, uint8_t delay)
{
    _min = min;
    _max = max;
    _reversed = reversed;
    _threshold = threshold;
    _delay = delay;
    setState(_min);
}

void DiscretePot::update()
{
    if (millis() > _lastUpdate + _delay) {
        int8_t valueNow = _value();
        if (valueNow != _state) {
            _counter++;
            if (_counter > _threshold) {
                setState(valueNow);
            } 
        } else if (_counter > 0) {
            _counter = 0;
        }
        _lastUpdate = millis();
    }
}

int8_t DiscretePot::value()
{
    return _state;
}

int8_t DiscretePot::_value()
{
    // 0 <= raw < 1024
    int raw = analogRead(_pin);
    int stepsize = 1023/(_max - _min);
    if (_reversed) {
        return _max-(raw/stepsize);
    } else {
        return (raw/stepsize)+_min;
    }
}

void DiscretePot::setState(int8_t newState)
{
    _lastStateChange = millis();
    _state = newState;
    _counter = 0;
}



