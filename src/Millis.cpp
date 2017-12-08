#include <Arduino.h>
#include "MutilaDebug.h"
#include "Millis.h"

float _MillisOffsetMs = 0.;

uint32_t Millis() {
    return millis() + (uint32_t)_MillisOffsetMs;
}

uint32_t MillisSince(uint32_t previousMs, uint32_t now)
{
    if (now == 0) {
        now = Millis();
    }

    return now >= previousMs ? (now - previousMs) : (0xFFFFFFFF - previousMs + now);
}

bool DoEvery(uint32_t periodMs, uint32_t& previousMs, uint32_t now)
{
    if (now == 0) {
        now = Millis();
    }

    if (MillisSince(previousMs, now) > periodMs) {
        previousMs = now;
        return true;
    } else {
        return false;
    }
}

void AddMillisOffset(float ms)
{
    _MillisOffsetMs += ms;
}

