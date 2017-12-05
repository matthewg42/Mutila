#pragma once

#include <stdint.h>

/*! Abstract button class.
 *
 *  Abstracts out a thing with on and off states, without saying
 *  what might cause those states
 */
class AbstractButton {
public:
    /*! Constructor.
     */
    AbstractButton() {;}

    /*! Initialization.
     *
     *  It is typical to call the begin() method from the 
     *  Arduino sketch's setup() function. This will call 
     *  pinMode() for you, with arguments appropriate for
     *  the button logic type.
     */
    virtual void begin() {;}

    /*! Test instantaneous input state.
     *
     *  \return true if the button is pushed, else false.
     */
    virtual bool on() = 0;

};


