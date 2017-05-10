#include "MutilaNeoPixel.h"
#include "Millis.h"

MutilaNeoPixel::MutilaNeoPixel(uint16_t n, uint8_t p, neoPixelType t=NEO_GRB + NEO_KHZ800) :
    Adafruit_NeoPixel(n, p, t)
{
}

void MutilaNeoPixel::show()
{
    Adafruit_NeoPixel::show();
    addMillisOffset(numPixels() * 0.0215);
}



