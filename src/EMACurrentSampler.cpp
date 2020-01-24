#include <Millis.h>
#include <EMACurrentSampler.h>
#include <VIPCalculation.h>

EMACurrentSampler::EMACurrentSampler(const uint8_t pin, 
                                     const float vSupply, 
                                     const float vRef,
                                     const float iOffset, 
                                     const millis_t periodMs,
                                     const float alpha) :
    EMASampler(pin, periodMs, alpha),
    _vSupply(vSupply),
    _vRef(vRef),
    _iOffset(iOffset)
{
}

float EMACurrentSampler::averageAmps()
{
    return currentConversion(average(), _vSupply, _vRef, _iOffset);
}

float EMACurrentSampler::lastAmps()
{
    return currentConversion(last(), _vSupply, _vRef, _iOffset);
}


