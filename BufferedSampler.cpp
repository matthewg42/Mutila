#include <Arduino.h>
#include "BufferedSampler.h"

BufferedSampler::BufferedSampler(const uint8_t pin, const uint8_t samples, const uint16_t periodMs) :
    AbstractSampler(pin, periodMs),
    _samples(samples),
    _idx(0),
    _count(0),
    _lastUpdated(0),
    _updated(false),
    _min(0),
    _max(0)
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
#ifdef DEBUG
    Serial.println(F("BufferedSampler::begin"));
#endif
    // Note: no need to set pinMode for analog inputs
}

void BufferedSampler::update() 
{
    if (_periodMs == 0 || millis() >= _lastUpdated + _periodMs || _lastUpdated == 0) {
        _sampleData[_idx] = analogRead(_pin);
#ifdef DEBUG
        Serial.print(F("BufferedSampler::update sample="));
        Serial.println(_sampleData[_idx]);
#endif
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
        _average = (float)sum/_count;
        _updated = false;
    }
}

