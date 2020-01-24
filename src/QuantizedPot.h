#pragma once 

#include <stdint.h>
#include "Millis.h"
#include "AbstractDebouncedButton.h"
#include "NumericRange.h"

/*! Use potential divider to select values based on specified ranges.
 *
 */
class QuantizedPot {
public:
    /*! Constructor.
     *
     *  \param pin the analog input pin to monitor (e.g. A0)
     *  \param maxRanges the maximum number of ranges we will want in our object
     */
    QuantizedPot(const uint8_t pin, int8_t maxRanges);

	/*! Destroctor
	 *  
	 *  de-allocates ranges
	 */
	~QuantizedPot();

	/*! Add a range to the object. Cannot add more than maxRanges (from constructor)
	 *  
	 *  \param start the first valid number of the range
	 *  \param end the last valid number of the range (not inclusive)
	 *
	 *  \return the index of the range in the object, or -1 if the range could not be added
	 */
	int8_t addRange(int start, int end);

    /*! Initializtion.
     *  
     *  \param threshold debouncing threshold (see DebouncedButton for details)
     *  \param delay debouncing delay (see DebouncedButton for details)
     */
    void begin(uint8_t threshold=AbstractDebouncedButton::DefaultThreshold, uint8_t delay=AbstractDebouncedButton::DefaultButtonDelay);

    /*! Allocate Timeslice.
     *
     *  This method must be called frequently - usually from loop()
     */
    void update();

    /*! Get value.
     *
     *  \returns Index of range presently selected, or -1 if no range selected.
     *           if more than once range is valid (overlapping ranges), the lowest
     *           index which is valid will be returned.
     */
    int8_t value();

	/*! Get velocity
	 *  
	 *  How far the current measurement is from the last measurement
	 */
	int velocity() { return _velocity; }

protected:
    const uint8_t _pin;
	int8_t _rangeMax;
	int8_t _rangeCount;
	NumericRange<int>** _ranges;
    uint8_t _threshold;
    uint8_t _delay;
    millis_t _lastUpdate;
    uint8_t _counter;
    int8_t _state;
    millis_t _lastStateChange;
	int _lastRaw;
	int _velocity;

    /*! Instantaneous value.
     *
     *  \return the index of the range the analog pin value is in at this instant.
     */
    int8_t _value();
    void setState(int8_t newState);

};

