#include <Arduino.h>
#include "Millis.h"

float _MillisOffsetMs = 0.;

unsigned long Millis() {
    return millis() + (unsigned long)_MillisOffsetMs;
}

unsigned long MillisSince(unsigned long previousMs, unsigned long now)
{
    now = now == 0 ? Millis() : now;
    return now > previousMs ? now - previousMs : 0xFFFFFFFF - previousMs + now;
}

void addMillisOffset(float ms)
{
    _MillisOffsetMs += ms;
}

