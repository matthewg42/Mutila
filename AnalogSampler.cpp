#include <Arduino.h>
#include "AnalogSampler.h"

AnalogSampler::AnalogSampler(const uint8_t pin, const uint8_t samples, const uint16_t periodMs) :
    AbstractSampler(pin, samples, periodMs),
    _idx(0),
    _lastUpdated(0),
    _updated(false)
{
    // Allocate ring buffer for sample data
    _sampleData = new int [samples];
}

AnalogSampler::~AnalogSampler()
{
    if (_sampleData != NULL) {
        delete _sampleData;
        _sampleData = NULL;
    }
}

void AnalogSampler::begin()
{
#ifdef DEBUG
    Serial.println(F("AnalogSampler::begin"));
#endif
    // Note: no need to set pinMode for analog inputs
}

void AnalogSampler::update() 
{
    if (_periodMs == 0 || millis() >= _lastUpdated + _periodMs || _lastUpdated == 0) {
        _sampleData[_idx] = analogRead(_pin);
#ifdef DEBUG
        Serial.print(F("AnalogSampler::update sample="));
        Serial.println(_sampleData[_idx]);
#endif
        _count = _count >= _samples ? _samples : _count+1;
        _idx = (_idx + 1) % _samples;
        _lastUpdated = millis();
        _updated = true;
    }
}

int AnalogSampler::last()
{
    return _count == 0 ? 0 :_sampleData[_idx == 0 ? _samples-1 : _idx-1];
}

void AnalogSampler::calculate() 
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

