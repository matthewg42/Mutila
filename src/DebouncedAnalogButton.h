#pragma once

#include <stdint.h>
#include "Mutila.h"
#include "AbstractDebouncedButton.h"
#include "AnalogButton.h"

/*! \brief Timeslice-based button with debouncing using analogRead
 *
 * DebouncedAnalogButton reduces / eliminates bouncing (multiple press
 * events registing close together with only one physical press).
 *
 * This class reads from the pin using analogRead. This is occasionally
 * useful when special analog-only pins need to be used for button inputs
 * (e.g. pins A6 and A7 on the nano).
 */
class DebouncedAnalogButton : public AbstractDebouncedButton, public AnalogButton {
public:
    /*! Constructor.
     *
     * \param pin the pin used for this button.
     * \param analogThreshold the value mid way between the on and off states as reported by analogRead.
     * \param invert if true, the logic of he button in inverted
     */
    DebouncedAnalogButton(const uint8_t pin, const uint16_t analogThreshold=512, const bool invert=false);

    /*! Initialization
     *
     * \param threshold how many tests of the pin must match for a state change
     * \param delay number of ms between tests of pin state
     *
     * Should be called from setup(), or at any rate, before
     * other members are called. This will set the pinMode. The
     * minimum time it takes for button presses / released to register
     * is threshold * delay.
     */
    void begin(uint8_t threshold=AbstractDebouncedButton::DefaultThreshold, uint8_t delay=AbstractDebouncedButton::DefaultButtonDelay);

    /*! Allocate Timeslice
     *
     * This method must be called frequently - usually from loop()
     */
    void update();

    /*! Test instantaneous input state (with debouncing)
     *
     * \return true if the button is pushed, else false.
     *
     */
    bool on();

};


