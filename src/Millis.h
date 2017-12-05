#pragma once

/*! \brief millis replacement
 *
 * The Arduino millis() function can have it's return value
 * messed up if a sketch disables and re-enables interrupts 
 * for some reason. This is commonly encountered when using
 * Adafruit's NeoPixel library, which disables interrupts
 * while sending data to Neopixel devices (as timing is critical)
 * Sketches which make heavy use of NeoPixels will encouter 
 * millis drift, where time is slowed down.
 *
 * Mutils provides Millis() as a replacement for the stock millis()
 * function, and a addMillisOffset() which can then be used to
 * compensate drift in the internal clock.  In the case of NeoPixel
 * show() calls, the drift is approximately proportional to the
 * number of NeoPixels which are updated, and so the millis offset
 * can be calculated and addMillisOffset() called to "fix" the clock.
 *
 */

//! Global Millis offset value.
extern float _MillisOffsetMs;

//! Replacement for millis() which uses millis offset as am adjustable correction.
unsigned long Millis(); 

//! Calculate millis since a timestamp, coping gracefully with wrapping around
//! the end of the millis() unsigned long range.
//!
//! \param previousMs the timestamp to calculate how long ago it was.
//! \param value of time to do calculation from. If 0, use Millis().
//
unsigned long MillisSince(unsigned long previousMs, unsigned long now=0);

//! Add offset
void addMillisOffset(float ms);


