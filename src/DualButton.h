#pragma once

#include "DebouncedButton.h"

/*! Single button object responding to two inputs
 *
 *  \deprecated This class is now deprecated and will be removed from
 *  Mutile in the near future. Please consider using DualInputButton 
 *  for instantaneous buttons, and DebouncedDualButton for a version
 *  with tapped() and other debounced features.
 *
 *  DualButton acts like a single button, but will respond to input
 *  from one of two separate DebouncedButtons on different pins and
 *  potentially with different pin logic. This makes it easy to have
 *  a second input (e.g. wired button and FM button) whilst 
 *  maintaining the clean syntax of a single button object in your
 *  sketch.
 *
 */
class DualButton {
public:
    /*! Constructor
     * \param b1 A pointer to a DebouncedButton object
     * \param v2 A pointer to a DebouncedButton object
     */
    DualButton(DebouncedButton* b1, DebouncedButton* b2);

    /*! Initialization
     *
     * \param threshold how many tests of the pin must match for a state change
     * \param delay number of ms between tests of pin state
     *
     * Should be called from setup(), or at any rate, before
     * other members are called. This will call the begin() method
     * in both of the linked DebouncedButtons.
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

    /*! Test if either button has been pushed since the last time it was off.
     *
     * The idea is that you can called pushed lots of times ina tight loop
     * and only get one true return pre press of the button regardless of
     * how many times you test.
     */
    bool pushed();

    /*! Test if either button has been pushed and released.
     *
     * \return true if either button has been tapped, else false.
     *
     */
    bool tapped();

    /*! Test if either button is held on for extended period
     *
     * \param ms time in ms the button has to have been on for to be considered held
     *
     * \return true if either button is pushed and has been for longer 
     *         than specified time.
     *
     */
    bool held(uint16_t ms=AbstractDebouncedButton::DefaultHeldMs);

    /*! Get periodic press results when either button is held.
     *
     * \param initialMs time between first press and first repeat in ms
     * \param repeatMs time between subsequent releats
     * \return true when either button is pushed, but only every so often...
     */
    bool repeat(uint16_t initialMs=AbstractDebouncedButton::DefaultButtonRepeatInitialMs, uint16_t repeatMs=AbstractDebouncedButton::DefaultButtonRepeatMs);

private:
    DebouncedButton* _b1;
    DebouncedButton* _b2;
};

