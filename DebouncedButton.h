#pragma once

#include <stdint.h>
#include "Mutila.h"
#include "RawButton.h"

/*! \brief Timeslice-based button with debouncing
 *
 * DebouncedButton reduces / eliminates bouncing (multiple press
 * events registing close together with only one physical press).
 *
 * The update() method must be called frequently (usually from 
 * loop()) to work properly.
 */
class DebouncedButton : public RawButton {
public:
    /*! Constructor
     *
     * \param pin the pin used for this button
     * \param pullup if true pin==LOW means on, else pin==HIGH is on
     */
    DebouncedButton(uint8_t pin, bool pullup=true);

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
    void begin(uint8_t threshold=DEBOUNCED_BUTTON_THRESHOLD, uint8_t delay=DEBOUNCED_BUTTON_DELAY);

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

    /*! Test if the button has been pushed since the last time it was off
     *
     * The idea is that you can called pushed lots of times ina tight loop
     * and only get one true return pre press of the button regardless of
     * how many times you test.
     */
    bool pushed();

    /*! Test if the button has been pushed and released.
     *
     * After returning a non-zero value (i.e. a tap was refistered), the
     * state will be reset. Only the last tap duration will be returned.
     *
     * \return length of last tap in ms if the button has been tapped, else 0.
     *
     */
    unsigned long tapped();

    /*! Test if held on for extended period
     *
     * \param ms time in ms the button has to have been on for to be considered held
     *
     * \return true if the button is pushed and has been for longer 
     *         than specified time.
     *
     */
    bool held(uint16_t ms=DEBOUNCED_BUTTON_HELD_MS);

    /*! Get periodic press results when button is held.
     *
     * \param initialMs time between first press and first repeat in ms
     * \param repeatMs time between subsequent releats
     * \return true when pushed every so often...
     */
    bool repeat(uint16_t initialMs=DEBOUNCED_BUTTON_RPT_INITIAL_MS, uint16_t repeatMs=DEBOUNCED_BUTTON_RPT_MS);

private:
    uint8_t _threshold;
    uint8_t _delay;
    unsigned long _lastUpdate;
    uint8_t _counter;
    bool _state;
    unsigned long _lastStateChange;
    bool _pushed;
    uint16_t _repeatCount;
    unsigned long _nextRepeatTime;
    unsigned long _lastOnDuration;

    void setState(bool newState);

};


