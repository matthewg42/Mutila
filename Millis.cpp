#include <Arduino.h>
#include "Millis.h"

float _MillisOffsetMs = 0.;

unsigned long Millis() {
    return millis() + (unsigned long)_MillisOffsetMs;
}

void addMillisOffset(float ms)
{
    _MillisOffsetMs += ms;
}

