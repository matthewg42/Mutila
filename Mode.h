#pragma once

#include "MutilaDebug.h"

/*! \brief Mode base class
 *
 * This is the base class.  We just ensure there are implementations of
 * important methods in derived classes so we have a nice common 
 * interface...
 *
 * To implement a mode:
 *    -# Create a class derived from Mode or BrownoutMode
 *    -# Implement modeStart(), modeStop(), and modeUpdate() in your class
 *    -# Optionally over-ride begin() if you have stuff to do in setup()
 *    -# If you want periodic calls to modeUpdate(), call setUpdatePeriod()
 *       from your class constructor
 *
 * To use a mode in a sketch:
 *    -# call begin() before use
 *    -# call start() when starting a mode (this will in turn call modeStart())
 *    -# call stop() when stopping a mode (this will in turn call modeStop())
 *    -# call update() frequently (this will in turn call modeUpdate())
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
     */
    void update() { 
        unsigned long now = millis();
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

