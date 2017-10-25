#include "BufferedVDivSampler.h"
#include "VIPCalculation.h"

BufferedVDivSampler::BufferedVDivSampler(const uint8_t pin, 
                                         const uint16_t r1KOhm, 
                                         const uint16_t r2KOhm, 
                                         const float vRef, 
                                         const uint16_t periodMs, 
                                         const uint8_t samples) :
    BufferedSampler(pin, periodMs, samples),
    _r1KOhm(r1KOhm),
    _r2KOhm(r2KOhm),
    _vRef(vRef)
{
}

float BufferedVDivSampler::averageVolts()
{
    return vDivVolts(average(), _r1KOhm, _r2KOhm, _vRef);
}

float BufferedVDivSampler::lastVolts()
{
    return vDivVolts(last(), _r1KOhm, _r2KOhm, _vRef);
}


