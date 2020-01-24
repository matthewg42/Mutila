#pragma once

#include <stdint.h>
#include <AbstractButton.h>

/*! Basic instantaneous button from two separate inputs.
 *
 *  DualInputButton models a digital push button or switch made 
 *  from two separate "child" buttons. The DualInputButton is 
 *  considered to be on if either of the two input buttons are 
 *  on.
 *
 */
class DualInputButton : public AbstractButton {
public:
    enum MixMode {
        Or,
        Xor,
        And
    };
public:
    /*! Constructor.
     *
     *  \param button1 a reference to the first button object.
     *  \param button2 a reference to the second button object.
     *  \param mix how to combine the two inputs.
     */
    DualInputButton(AbstractButton& button1, AbstractButton& button2, const MixMode mix=Or);

    /*! Initialization.
     *
     *  \param callBeginInChildren if true, begin() will be called in
     *         the two button objects referenced in the constructor.
     *         If false, that will be left to the user (in case they
     *         want to call begin with non-defalt parameters).
     */
    void begin(bool callBeginInChildren=true);

    /*! Test instantaneous input state.
     *
     *  \return true if either child button is pressed, else false.
     */
    bool on();

protected:
    AbstractButton& _button1;
    AbstractButton& _button2;
    const MixMode _mix;

};

