#pragma once

#include <Mode.h>

// ModeOne_ prints a message to Serial every half a second
// ModeOne_ terminated when ButtonA is pushed.
class ModeOne_ : public Mode {
public:
    ModeOne_();
    void modeStart();
    void modeStop();
    void modeUpdate();

};

// A global object for this class, in the same style as the Arduino Serial object
extern ModeOne_ ModeOne;

