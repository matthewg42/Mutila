#pragma once

#include <Mode.h>

// ModeA1_ prints a message to Serial every half a second
class ModeA1_ : public Mode {
public:
    ModeA1_();
    void begin();
    void modeStart();
    void modeStop();
    void modeUpdate();

private:
    unsigned int counter;

};

// A global object for this class, in the same style as the Arduino Serial object
extern ModeA1_ ModeA1;

