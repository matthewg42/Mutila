#pragma once

#include "DebouncedButton.h"

/*! PushButton which toggles state.
 *
 *  Push once - on.  Push again - off.
 */
class ToggleButton {
public:
    /*! Constructor.
     *
     * \param pin the pin which he button is connected to.
     * \param pullup sets the logic type for the button.
     *
     * Note: if pullup is true the logic of the button is
     * inverted - i.e. when the pin in pulled to ground, the
     * button is considered to be pushed/on. The default is
     * pullup, meaning that a LOW state on the pin means
     * the button is on. Whilst this is a bit counter-intuitive,
     * it is preferred as a floating pin will revert to off
     * more readily than with non-pullup logic.
     */
    ToggleButton(uint8_t pin, bool pullup=true);

    /*! Initialization.
     *
     * \param startState which state (on or off) the toggle starts in.
     * \param threshold how many tests of the pin must match for a press detection.
     * \param delay number of ms between tests of press detection.
     *
     * Should be called from setup(), or at any rate, before
     * other members are called. This will set the pinMode. The
     * minimum time it takes for button presses / released to register
     * is threshold * delay.
     */
    void begin(bool startState=false, uint8_t threshold=DEBOUNCED_BUTTON_THRESHOLD, uint8_t delay=DEBOUNCED_BUTTON_DELAY);

    /*! Allocate Timeslice.
     *
     * This method must be called frequently - usually from loop().
     */
    void update();

    /*! Test toggle state.
     *
     * \return true if the toggle is on, else false.
     *
     */
    bool on();

private:
    DebouncedButton _button;
    bool _toggled;

};

