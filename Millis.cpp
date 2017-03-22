#include <Arduino.h>
#include "Millis.h"

float _MillisOffsetMs = 0.;

tMillis Millis() {
    return millis() + (tMillis)_MillisOffsetMs;
}

void addMillisOffset(float ms)
{
    _MillisOffsetMs += ms;
}

