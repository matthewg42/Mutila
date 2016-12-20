#pragma once

/*! \brief Mode base class
 *
 * This is the base class.  We just ensure there are implementations of
 * important methods in derived classes so we have a nice common 
 * interface...
 */
class Mode {
public:
    /*! Initialization
     *
     * Over-ride in derived classes if you need to do something from setup().
     */
    virtual void begin() {;}

    /*! Mode start (or re-start)
     *
     * Implement in derived classes - executed when mode is started.
     */
    virtual void start() = 0;

    /*! Mode stop
     *
     * Implement in derived classes - executed when mode is stopped.
     */
    virtual void stop() = 0;

    /*! Mode update
     *
     * Implement in derived classes - executed frequently, typically from loop().
     */
    virtual void update() = 0;

    /*! mode reset
     *
     * Over-ride in derived classes - called when reset (when mode is restarted without switching from another mode).
     */
    virtual void reset() { start(); }

    /*! Report mode self-termination
     *
     * Provide a mechanism for modes to tell the main loop they're finished - over-ride if desired.
     */
    virtual bool isFinished() { return false; }

};

