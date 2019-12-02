#pragma once

#include <Mode.h>

// ModeOneClass prints a message to Serial every half a second
// ModeOneClass terminated when Button is pushed.
class ModeOneClass : public Mode {
public:
    ModeOneClass();
    void modeStart();
    void modeStop();
    void modeUpdate();

};

// A global object for this class, in the same style as the Arduino Serial object
extern ModeOneClass ModeOne;

