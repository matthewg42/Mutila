#include "MutilaNeoPixel.h"
#include "Millis.h"

MutilaNeoPixel::MutilaNeoPixel(uint16_t n, uint8_t p, neoPixelType t) :
    Adafruit_NeoPixel(n, p, t)
{
}

void MutilaNeoPixel::show()
{
    Adafruit_NeoPixel::show();
    addMillisOffset(numPixels() * 0.0215);
}



