#pragma once

#include <stdint.h>
#include <AbstractDebouncedButton.h>
#include <DualInputButton.h>
#include <AbstractButton.h>

/*! Timeslice-based dual input button with debouncing
 *
 *  This class adds debouncing to a DualInputButton.
 */
class DebouncedDualButton : public AbstractDebouncedButton, public DualInputButton {
public:
    /*! Constructor.
     *
     *  \param button1 a reference to the first button input.
     *  \param button2 a reference to the second button input.
     */
    DebouncedDualButton(AbstractButton& button1, AbstractButton& button2);

    /*! Initialization.
     *
     *  \param callBeginInChildren if true, begin() will be called in
     *         the two button objects referenced in the constructor.
     *         If false, that will be left to the user (in case they
     *         want to call begin with non-defalt parameters).
     *  \param threshold how many tests of the pin must match for a state change.
     *  \param delay number of ms between tests of pin state.
     *
     *  Should be called from setup(), or at any rate, before
     *  other members are called. This will set the pinMode. The
     *  minimum time it takes for button presses / released to register
     *  is threshold * delay.
     */
    void begin(bool callBeginInChildren=true, uint8_t threshold=AbstractDebouncedButton::DefaultThreshold, uint8_t delay=AbstractDebouncedButton::DefaultButtonDelay);

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


