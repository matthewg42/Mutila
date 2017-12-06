#include <Arduino.h>
#include <Millis.h>
#include "EMASonicRanger.h"

EMASonicRanger::EMASonicRanger(const uint8_t trigPin, const uint8_t echoPin, const uint16_t periodMs, const float alpha, uint16_t minimumRange) :
    SonicRanger(trigPin, echoPin),
    _periodMs(periodMs),
    _alpha(alpha),
    _minimumRange(minimumRange)
{
}

void EMASonicRanger::begin()
{
    SonicRanger::begin();
    _lastUpdated = Millis();
    _movingAverage = SonicRanger::getRange();
    _lastSample = _movingAverage;
}

void EMASonicRanger::update()
{
    if (_periodMs == 0 || MillisSince(_lastUpdated) >= _periodMs) {
        uint16_t sample = SonicRanger::getRange();
        if (sample >= _minimumRange) {
            _lastSample = sample;
            _movingAverage = (_alpha*_lastSample) + ((1-_alpha)*_movingAverage);
            _lastUpdated = Millis();
        }
    }
}

uint16_t EMASonicRanger::getRange()
{
    return _movingAverage;
}


