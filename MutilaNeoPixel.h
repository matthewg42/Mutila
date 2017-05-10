#pragma once
#include <Adafruit_NeoPixel.h>

/*! \brief MutilaNeoPixel 
 *
 * When the Adafruit_NeoPixel.show() member is called interrupts are 
 * temporarily disabled to allow the precise timing required when
 * sending data out to the WS2811 LEDs.  This has a few side-effects,
 * including a drift in the timer which is used by millis().
 *
 * This is usually a small effect, but when a long strip of LEDs is 
 * updated frequently, the offset can add up and become noticable. In
 * one application, the author noticed the value of millis being 50%
 * slower than real time!
 *
 * This class is a simple sub-class of the Adafruit_NeoPixel class
 * which estimates the offset to the millis timer, and updates the
 * offset used in Mutila's Millis() call.
 */
class MutilaNeoPixel : public Adafruit_NeoPixel {
public:
    //! Construct a MutilaNeoPixel object
    MutilaNeoPixel(uint16_t n, uint8_t p=6, neoPixelType t=NEO_GRB + NEO_KHZ800);

    //! Send updated pixel state to LEDs, and update Millis() offset
    void show(void);

};

