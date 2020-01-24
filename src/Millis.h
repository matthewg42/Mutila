#pragma once

#include <stdint.h>

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
 * Mutila provides Millis() as a replacement for the stock millis()
 * function, and a addMillisOffset() which can then be used to
 * compensate drift in the internal clock.  In the case of NeoPixel
 * show() calls, the drift is approximately proportional to the
 * number of NeoPixels which are updated, and so the millis offset
 * can be calculated and addMillisOffset() called to "fix" the clock.
 *
 */

/*! The type that should be used whenever Millis is used, and should match
 *  what the Arduino-provided millis() function returns.
 *  To the author's knowlegde, this is unsigned long, but it could
 *  conceivably be something different on some boards. If so then this typedef
 *  will have to vary according to board #defines
 */
typedef unsigned long millis_t;

/*! The type that is returned by micros() */
typedef unsigned long micros_t;

/*! Global Millis offset value.
 */
extern float _MillisOffsetMs;

/*! Replacement for millis() which uses millis offset as am adjustable correction.
 *
 *  \return number of milliseconds since the sketch started running, plus
 *          the offset as modified by addMillisOffset.
 */
millis_t Millis(); 

/*! Calculate millis since a timestamp.
 *
 *  This function handles wrapping of Millis around the 32 bit unsigned integer
 *  maximum gracefully.
 *
 *  \param previousMs the timestamp to calculate how long ago it was.
 *  \param value of time to do calculation from. If 0, use Millis().
 *  \return the number of milliseconds since the last time Millis() was previousMs.
 */
millis_t MillisSince(millis_t previousMs, millis_t now=0);

/*! Trigger events based on previous occurance and an interval.
 *
 *  Note: this function modifies the referenced previousMs variable.
 *
 *  \param previousMs a reference to a variable used to track the last time
 *         an event was triggered.
 *  \param periodMs how often (in ms) the event is expected to trigger.
 *  \param now a value to use instead of calling Millis().
 *  \return true if periodMs has elapsed since previousMs, else false.
 */
bool DoEvery(millis_t periodMs, millis_t& previousMs, millis_t now=0);

/*! Add offset to Millis() results.
 *
 *  \param ms offset in milliseconds.
 */
void AddMillisOffset(float ms);

/*! Add offset to Millis() results.
 *
 * \deprecated Please use AddMillisOffset for new code.
 *  \param ms offset in milliseconds.
 */
#define addMillisOffset(ms) do { AddMillisOffset(ms); } while(0)


