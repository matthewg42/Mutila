#include <Millis.h>
#include <EMAVDivSampler.h>
#include <VIPCalculation.h>

EMAVDivSampler::EMAVDivSampler(const uint8_t pin, 
                               const uint16_t r1KOhm, 
                               const uint16_t r2KOhm, 
                               const float vRef, 
                               const millis_t periodMs,
                               const float alpha) :
    EMASampler(pin, periodMs, alpha),
    _r1KOhm(r1KOhm),
    _r2KOhm(r2KOhm),
    _vRef(vRef)
{
}

float EMAVDivSampler::averageVolts()
{
    return vDivVolts(average(), _r1KOhm, _r2KOhm, _vRef);
}

float EMAVDivSampler::lastVolts()
{
    return vDivVolts(last(), _r1KOhm, _r2KOhm, _vRef);
}


