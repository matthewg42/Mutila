#pragma once

#include <stdint.h>
#include <Millis.h>
#include <AbstractButton.h>

/*! Timeslice-based button with debouncing.
 *
 *  AbstractDebouncedButton reduces / eliminates bouncing (multiple press
 *  events registing close together with only one physical press).
 */
class AbstractDebouncedButton : public AbstractButton {
public:
    static const uint8_t DefaultThreshold = 5;
    static const uint8_t DefaultButtonDelay = 5;
    static const uint16_t DefaultHeldMs = 800;
    static const uint16_t DefaultButtonRepeatInitialMs = 700;
    static const uint16_t DefaultButtonRepeatMs = 350;

public:
    /*! Constructor.
     */
    AbstractDebouncedButton();

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
    void begin(uint8_t threshold=DefaultThreshold, uint8_t delay=DefaultButtonDelay);

    /*! Allocate timeslice.
     *
     *  This method must be called frequently - usually from loop().
     */
    virtual void update() = 0;

    /*! Test if the button has been pushed since the last time it was off.
     *
     *  This function returns true once, as soon as the button is pushed - 
     *  even if it has not been released yet. If the peek parameter is false
     *  then subsequent calls to pushed will not return true until the button
     *  has been released and pushed again. The idea is to allow frequent 
     *  tests in a tight loop, and only get one positive result (unlike on(),
     *  which returns true any time the button is depressed).
     *
     *  \param peek if true, do not reset the pushed state.
     *  \return true if the button has been pushed and released since the
     *          last test.
     */
    bool pushed(bool peek=false);

    /*! Test if the button has been pushed and released.
     *
     *  After returning a non-zero value (i.e. a tap was registered), the
     *  state will be reset. Only the last tap duration will be returned.
     *
     *  \param peek if true, do not reset the pushed state.
     *  \return length of last tap in ms if the button has been tapped, else 0.
     */
    millis_t tapped(bool peek=false);

    /*! Test if held on for extended period.
     *
     *  \param ms time in ms the button has to have been on for to be considered held
     *
     *  \return true if the button is pushed and has been for longer 
     *          than specified time.
     */
    bool held(uint16_t ms=DefaultHeldMs);

    /*! Get periodic press results when button is held.
     *
     *  \param initialMs time between first press and first repeat in ms.
     *  \param repeatMs time between subsequent releats.
     *  \return true when pushed every so often...
     */
    bool repeat(uint16_t initialMs=DefaultButtonRepeatInitialMs, uint16_t repeatMs=DefaultButtonRepeatMs);

    /*! Explicitly set the state of the button.
     *
     *  \param newState the new state to have.
     */
    void setState(bool newState);

protected:
    uint8_t _threshold;
    uint8_t _delay;
    millis_t _lastUpdate;
    uint8_t _counter;
    bool _state;
    millis_t _lastStateChange;
    bool _pushed;
    uint16_t _repeatCount;
    millis_t _lastRepeat;
    millis_t _lastOnDuration;

};


