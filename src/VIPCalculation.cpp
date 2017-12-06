#include "VIPCalculation.h"

float vDivVolts(const int16_t value, const uint16_t r1KOhm, const uint16_t r2KOhm, const float vRef)
{
    return (value*vRef*(r1KOhm+r2KOhm)) / (1024.0*r1KOhm);
}

float currentConversion(const int16_t value, const float vSupply, const float vRef, const float iOffset)
{
    return ((vSupply/2.0)-((vRef+iOffset)*value/1024.0)) / (0.04*vSupply/(vRef+iOffset));
}

