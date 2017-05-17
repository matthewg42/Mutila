#include <Arduino.h>
#include <Millis.h>
#include "SonicRanger.h"

SonicRanger::SonicRanger(const uint8_t trigPin, const uint8_t echoPin) :
    _trigPin(trigPin),
    _echoPin(echoPin),
    _maxCm(SONIC_RANGE_DEFAULT_MAX_CM),
    _timeoutMs(SONIC_RANGE_DEFAULT_TIMEOUT_MS)
{
}

void SonicRanger::begin()
{
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

uint16_t SonicRanger::getRange()
{
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    unsigned long b4 = Millis();
    digitalWrite(_trigPin, LOW);
    unsigned long time = pulseInLong(_echoPin, HIGH, _timeoutMs*1000UL);
    unsigned long after = Millis();
    if (after - b4 >= _timeoutMs) {
        return _maxCm;
    } else {
        return time*0.034/2;
    }
}

