#pragma once

#include "Mode.h"

/*! ModeManager class for switching between mutually exclusive Modes.
 */
class ModeManagerClass {
public:
    ModeManagerClass();

    /*! Initialization.
     *
     *  Typically called from setup().
     *
     *  \param initialMode the mode to start in.
     */
    void begin(Mode* initialMode);

    /*! Allocate timeslice.
     *
     * Called frequently to update the current mode, typically from loop().
     */
    void update();

    /*! Change Mode.
     *
     *  Call to end the current Mode and start the new Mode.
     *
     *  \param newMode the new mode to switch to.
     *  \param force calling stop in current mode and start in new mode, 
     *         even if they are the same.
     */
    void switchMode(Mode* newMode, bool force=false);

    /*! Check to see if the current mode is finished.
     *
     *  \return true if the current Mode is finished, else false.
     */
    bool modeFinished();

    /* A pointer to the current mode object.
     */
    Mode* currentMode; 

};

