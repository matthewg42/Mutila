#pragma once

#include "Mode.h"

/*! A Mode With Modes of it's own
 *
 *  A Parent Mode has one or more child Modes. One of these child modes is
 *  active at any one time. When the ParentModes update() member is called, 
 *  the currently-active child Mode's update() is called.
 *
 *  Child Modes may themselves be a ParentMode, allowing for hierarchies of
 *  Modes.
 *
 *  It is customary for a ParentMode to implement the begin() member, and
 *  use it to call begin() for all of it's child modes. In this way the
 *  sketch which pulls in a ParentMode and it's tree of child modes must
 *  only call begin() for that one ParentMode.
 */

class ParentMode : public Mode {
public:
    //! Constructor
    ParentMode();

    /*! Switch child mode
     *
     * \param newMode the address of the child Mode to switch to
     */
    void switchMode(Mode* newMode);

protected:
    Mode* pMode;

};

