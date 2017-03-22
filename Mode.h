#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "MutilaDebug.h"
#include "Millis.h"

/*! \brief Mode base class
 *
 * This is the base class.  We just ensure there are implementations of
 * important methods in derived classes so we have a nice common 
 * interface...
 *
 * To implement a mode:
 *    -# Create a class derived from Mode
 *    -# Implement modeUpdate() in your class to do mode-specific things
 *    -# Optionally over-ride begin(), modeStart() and modeStop()
 *    -# If you want periodic calls to modeUpdate(), call setUpdatePeriod()
 *       from your class constructor
 *
 * To use a mode in a sketch:
 *    -# call begin() before use
 *    -# call start() when starting a mode (this will in turn call modeStart())
 *    -# call stop() when stopping a mode (this will in turn call modeStop())
 *    -# call update() frequently (this will in turn call modeUpdate())
 *
 * A typical sketch will switch modes by calling a function like this:
 * \code{.cpp}
 *   Mode* CurrentMode;
 *   ...
 *   void switchMode(Mode* newMode)
 *   {
 *       CurrentMode->stop();
 *       CurrentMode = newMode;
 *       CurrentMode->start();
 *   }
 * \endcode
 */
class Mode {
public:
    //! Constructor
    Mode() : _lastUpdateMs(0), _updatePeriodMs(0) {;}

    /*! Initialization
     *
     * Over-ride in derived classes if you need to do something from setup().
     */
    virtual void begin() {;}

    /*! Report mode self-termination
     *
     * Provide a mechanism for modes to tell the main loop they're finished - over-ride if desired.
     */
    virtual bool isFinished() { return false; }

    //! To be called when switching to this mode
    void start() { _lastUpdateMs = 0; modeStart(); }

    //! To be called when switching to another mode
    void stop() { modeStop(); }

    /*! Allocate timeslice
     *
     * This should be called frequently (typically from loop()).  It will in turn
     * call modeUpdate(), which must be implemented in all derived classes, and
     * should contain user-code to be executed frequently.
     *
     * It is not generally implemeneted in normal derived classes - modeUpdate() 
     * should be used instead for class secific updates. If it is, it should call 
     * Mode::update().
     *
     */
    virtual void update() { 
        unsigned long now = Millis();
        if (now >= _lastUpdateMs + _updatePeriodMs || _lastUpdateMs==0) {
            modeUpdate();
            _lastUpdateMs = now;
        }
    }

    /*! Set update period
     * \param periodMs sets the minimum time between calls to modeUpdate() from update() in 
     *                 milliseconds.
     */
    void setUpdatePeriod(uint16_t periodMs) { _updatePeriodMs = periodMs; }

protected:
    /*! Mode start (or re-start)
     *
     * Over-ride in derived classes - executed when mode is started.
     */
    virtual void modeStart() {;}

    /*! Mode stop
     *
     * Over-ride in derived classes - executed when mode is stopped.
     */
    virtual void modeStop() {;}

    /*! Mode update
     *
     * Implement in derived classes - will be called from update(), but only if
     * _updatePeriodMs has passed since the last invocation.
     */
    virtual void modeUpdate() = 0;

    unsigned long _lastUpdateMs;
    uint16_t _updatePeriodMs;

};

