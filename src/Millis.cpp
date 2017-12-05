#include <Arduino.h>
#include "Millis.h"

float _MillisOffsetMs = 0.;

uint32_t Millis() {
    return millis() + (uint32_t)_MillisOffsetMs;
}

uint32_t MillisSince(uint32_t previousMs, uint32_t now)
{
    now = now == 0 ? Millis() : now;
    return now > previousMs ? now - previousMs : 0xFFFFFFFF - previousMs + now;
}

void addMillisOffset(float ms)
{
    _MillisOffsetMs += ms;
}

