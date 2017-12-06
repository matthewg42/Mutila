#pragma once

#include <stdint.h>
#include "AbstractButton.h"

/*! Instantaneous button with a digital output, from an analog input.
 *
 *  AnalogButton models a digital push button or switch attached 
 *  to an analog input. The API gives the user a logical pushed
 *  state via the on() method, which hides the analog to digital 
 *  logic from the user of the class (choose logic params in 
 *  constructor).
 *
 *  Usually, a digital RawButton will be better, but a few pins on
 *  some microcontrollers (A6, A7 on the Nano, for example), cannot
 *  read in digitial mode, so this lets those pins be used as
 *  buttons.
 */
class AnalogButton : public AbstractButton {
public:
    /*! Constructor.
     *
     *  \param pin the pin which he button is connected to.
     *  \param pullup if true pin==LOW means on, else pin==HIGH is on.
     *  \param analogThreshold the value above which the button 
     *         is considered to be on.
     *
     *  Note: it is typical for digital buttons to be held high by a 
     *  pullup resistor (either internal or external) pullup, and 
     *  activated by pulling the pin to ground. This "inverted logic" 
     *  is replicated here with the default value of pullup. However, 
     *  there is no internal pullup resistor some analog pins, so an 
     *  external pullup should be used where necessary.
     */
    AnalogButton(const uint8_t pin, const bool pullup=true, const uint16_t analogThreshold=512);

    /*! Initialization.
     *
     *  It is typical to call the begin() method from the 
     *  Arduino sketch's setup() function. This will call 
     *  pinMode() for you, with arguments appropriate for
     *  the button logic type.
     */
    void begin();

    /*! Test instantaneous input state.
     *
     *  \return true if the button is pushed, else false.
     */
    bool on();

protected:
    const uint8_t _pin;
    const bool _pullup;
    const uint16_t _analogThreshold;

};

