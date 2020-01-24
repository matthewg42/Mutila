#pragma once

#include <stdint.h>
#include <AbstractButton.h>

/*! Basic instantaneous button from a digital input.
 *
 *  DigitalInputButton models a digital push button or switch attached 
 *  to a digital input. The API gives the user a logical pushed
 *  state via the on method, which hides inverted level 
 *  logic from the user of the class (choose logic type in 
 *  constructor).
 */
class DigitalInputButton : public AbstractButton {
public:
    /*! Constructor.
     *
     *  \param pin the pin which he button is connected to.
     *  \param pullup sets the logic type for the button.
     *
     *  Note: if pullup is true the logic of the button is
     *  inverted - i.e. when the pin in pulled to ground, the
     *  button is considered to be pushed/on. The default is
     *  pullup, meaning that a LOW state on the pin means
     *  the button is on. Whilst this is a bit counter-intuitive,
     *  it is preferred as a floating pin will revert to off
     *  more readily than with non-pullup logic.
     */
    DigitalInputButton(const uint8_t pin, const bool pullup=true);

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

};

