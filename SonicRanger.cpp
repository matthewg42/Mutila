#include <Arduino.h>
#include "SonicRanger.h"

SonicRanger::SonicRanger(const uint8_t trigPin, const uint8_t echoPin) :
    _trigPin(trigPin),
    _echoPin(echoPin)
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
    digitalWrite(_trigPin, LOW);
    long time = pulseIn(_echoPin, HIGH);
    return time*0.034/2;
}

