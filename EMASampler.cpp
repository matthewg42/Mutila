#include <Arduino.h>
#include "MutilaDebug.h"
#include "EMASampler.h"

EMASampler::EMASampler(const uint8_t pin, const uint16_t periodMs, const float alpha) :
    AbstractSampler(pin, periodMs),
    _alpha(alpha),
    _lastUpdated(0),
    _movingAverage(0.),
    _lastSample(0)
{
}

void EMASampler::begin()
{
    _DBLN(F("EMASampler::begin"));
    // Note: no need to set pinMode for analog inputs
    _lastUpdated = millis();
    _movingAverage = analogRead(_pin);
    _lastSample = _movingAverage;
}

void EMASampler::update() 
{
    if (_periodMs == 0 || millis() >= _lastUpdated + _periodMs || _lastUpdated == 0) {
        _lastSample = analogRead(_pin);
        _DB(F("EMASampler::update sample="));
        _DBLN(_lastSample);
        _movingAverage = (_alpha*_lastSample) + ((1-_alpha)*_movingAverage);
        _lastUpdated = millis();
    }
}



