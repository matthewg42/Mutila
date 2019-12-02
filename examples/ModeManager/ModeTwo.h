#pragma once

#include <Mode.h>

// ModeTwoClass prints a message to Serial every half a second
// ModeTwoClass terminated when Button is pushed.
class ModeTwoClass : public Mode {
public:
    ModeTwoClass();
    void modeStart();
    void modeStop();
    void modeUpdate();
    bool isFinished();

};

// A global object for this class, in the same style as the Arduino Serial object
extern ModeTwoClass ModeTwo;

