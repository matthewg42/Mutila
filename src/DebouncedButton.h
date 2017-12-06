#pragma once

#include <stdint.h>
#include "AbstractDebouncedButton.h"
#include "DigitalInputButton.h"

/*! Timeslice-based button with debouncing
 *
 *  DebouncedButton reduces / eliminates bouncing (multiple press
 *  events registing close together with only one physical press).
 *
 *  The update() method must be called frequently (usually from 
 *  loop()) to work properly.
 */
class DebouncedButton : public AbstractDebouncedButton, public DigitalInputButton {
public:
    /*! Constructor.
     *
     *  \param pin the pin used for this button.
     *  \param pullup if true pin==LOW means on, else pin==HIGH is on.
     */
    DebouncedButton(uint8_t pin, bool pullup=true);

    /*! Initialization.
     *
     *  \param threshold how many tests of the pin must match for a state change.
     *  \param delay number of ms between tests of pin state.
     *
     *  Should be called from setup(), or at any rate, before
     *  other members are called. This will set the pinMode. The
     *  minimum time it takes for button presses / released to register
     *  is threshold * delay.
     */
    void begin(uint8_t threshold=AbstractDebouncedButton::DefaultThreshold, uint8_t delay=AbstractDebouncedButton::DefaultButtonDelay);

    /*! Allocate timeslice.
     *
     *  This method must be called frequently - usually from loop().
     */
    void update();

    /*! Test instantaneous input state (with debouncing).
     *
     *  \return true if the button is pushed, else false.
     */
    bool on();

};


