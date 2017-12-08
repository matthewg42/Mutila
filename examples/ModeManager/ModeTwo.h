#pragma once

#include <Mode.h>

// ModeTwo_ prints a message to Serial every half a second
// ModeTwo_ terminated when Button is pushed.
class ModeTwo_ : public Mode {
public:
    ModeTwo_();
    void modeStart();
    void modeStop();
    void modeUpdate();
    bool isFinished();

};

// A global object for this class, in the same style as the Arduino Serial object
extern ModeTwo_ ModeTwo;

