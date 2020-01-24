#include <Arduino.h>
#include "MutilaDebug.h"
#include "Millis.h"

float _MillisOffsetMs = 0.;

millis_t Millis() {
    return millis() + (millis_t)_MillisOffsetMs;
}

millis_t MillisSince(millis_t previousMs, millis_t now)
{
    if (now == 0) {
        now = Millis();
    }

    return now >= previousMs ? (now - previousMs) : (0xFFFFFFFF - previousMs + now);
}

bool DoEvery(millis_t periodMs, millis_t& previousMs, millis_t now)
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

