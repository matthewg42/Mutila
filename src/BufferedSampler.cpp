#include <Arduino.h>
#include "MutilaDebug.h"
#include "Millis.h"
#include "BufferedSampler.h"

BufferedSampler::BufferedSampler(const uint8_t pin, const millis_t periodMs, const uint8_t samples) :
    AbstractSampler(pin, periodMs),
    _samples(samples),
    _idx(0),
    _count(0),
    _lastUpdated(0),
    _updated(false),
    _minimum(0),
    _maximum(0),
    _mean(0)
{
    // Allocate ring buffer for sample data
    _sampleData = new int16_t [samples];
}

BufferedSampler::~BufferedSampler()
{
    if (_sampleData != NULL) {
        delete _sampleData;
        _sampleData = NULL;
    }
}

void BufferedSampler::begin()
{
    _DBLN(F("BufferedSampler::begin"));
    // Note: no need to set pinMode for analog inputs
    _count = 0;
    _minimum = 0;
    _maximum = 0;
    _mean = 0;
    _lastUpdated = 0;
    _updated = false;
}

void BufferedSampler::update() 
{
    if (_periodMs == 0 || MillisSince(_lastUpdated) >= _periodMs || _count == 0) {
        _sampleData[_idx] = analogRead(_pin);
        _DB(F("BufferedSampler::update sample="));
        _DBLN(_sampleData[_idx]);
        _count = _count >= _samples ? _samples : _count+1;
        _idx = (_idx + 1) % _samples;
        _lastUpdated = Millis();
        _updated = true;
    }
}

int16_t BufferedSampler::last()
{
    return _count == 0 ? 0 : _sampleData[_idx == 0 ? _samples-1 : _idx-1];
}

void BufferedSampler::calculate() 
{
    if (_updated) {
        int32_t sum = _sampleData[0];
        _minimum = _sampleData[0];
        _maximum = _sampleData[0];
        for (uint8_t i=1; i<_count; i++) {
            sum += _sampleData[i];
            if (_sampleData[i] < _minimum) _minimum = _sampleData[i];
            if (_sampleData[i] > _maximum) _maximum = _sampleData[i];
        }
        _mean = (float)sum/_count;
        _updated = false;
    }
}

