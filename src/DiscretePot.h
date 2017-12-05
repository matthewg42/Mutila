#pragma once

#include <stdint.h>
#include "Mutila.h"

/*! Discrete values from a potential divider.
 *
 *  Monitors an analog input pin and converts the voltage on the
 *  input to a discrete value within a specified range (the default
 *  goes up to 11).
 */
class DiscretePot {
public:
    /*! Constructor.
     *
     *  \param pin the analog input pin to monitor (e.g. A0)
     */
    DiscretePot(const uint8_t pin);

    /*! Initializtion.
     *  
     *  \param min the minimum value
     *  \param max the maximum value
     *  \param reversed set to true to reverse the scale (return max when analogRead is at 0)
     *  \param threshold debouncing threshold (see DebouncedButton for details)
     *  \param delay debouncing delay (see DebouncedButton for details)
     */
    void begin(int8_t min=0, int8_t max=11, bool reversed=false, uint8_t threshold=DEBOUNCED_BUTTON_THRESHOLD, uint8_t delay=DEBOUNCED_BUTTON_DELAY);

    /*! Allocate Timeslice.
     *
     *  This method must be called frequently - usually from loop()
     */
    void update();

    /*! Get value.
     *
     *  \return Current value for the pot.
     */
    int8_t value();

private:
    const uint8_t _pin;
    int8_t _min;
    int8_t _max;
    bool _reversed;
    uint8_t _threshold;
    uint8_t _delay;
    uint32_t _lastUpdate;
    uint8_t _counter;
    int8_t _state;
    uint32_t _lastStateChange;

    /*! Instantaneous value.
     *
     *  Converts raw analogRead into value where: min <= value <= max.
     */
    int8_t _value();
    void setState(int8_t newState);

};

