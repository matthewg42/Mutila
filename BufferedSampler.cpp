#include <Arduino.h>
#include "MutilaDebug.h"
#include "Millis.h"
#include "BufferedSampler.h"

BufferedSampler::BufferedSampler(const uint8_t pin, const uint16_t periodMs, const uint8_t samples) :
    AbstractSampler(pin, periodMs),
    _samples(samples),
    _idx(0),
    _count(0),
    _lastUpdated(0),
    _updated(false),
    _min(0),
    _max(0),
    _mean(0)
{
    // Allocate ring buffer for sample data
    _sampleData = new int [samples];
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
    _min = 0;
    _max = 0;
    _mean = 0;
    _lastUpdated = 0;
    _updated = false;
}

void BufferedSampler::update() 
{
    if (_periodMs == 0 || millis() >= _lastUpdated + _periodMs || _lastUpdated == 0) {
        _sampleData[_idx] = analogRead(_pin);
        _DB(F("BufferedSampler::update sample="));
        _DBLN(_sampleData[_idx]);
        _count = _count >= _samples ? _samples : _count+1;
        _idx = (_idx + 1) % _samples;
        _lastUpdated = millis();
        _updated = true;
    }
}

int BufferedSampler::last()
{
    return _count == 0 ? 0 : _sampleData[_idx == 0 ? _samples-1 : _idx-1];
}

void BufferedSampler::calculate() 
{
    if (_updated) {
        long sum = _sampleData[0];
        _min = _sampleData[0];
        _max = _sampleData[0];
        for (uint8_t i=1; i<_count; i++) {
            sum += _sampleData[i];
            if (_sampleData[i] < _min) _min = _sampleData[i];
            if (_sampleData[i] > _max) _max = _sampleData[i];
        }
        _mean = (float)sum/_count;
        _updated = false;
    }
}

