#pragma once

#include <Mode.h>

// ModeA2_ prints a message to Serial every half a second
class ModeA2_ : public Mode {
public:
    ModeA2_();
    void begin();
    void modeStart();
    void modeStop();
    void modeUpdate();

private:
    unsigned int counter;

};

// A global object for this class, in the same style as the Arduino Serial object
extern ModeA2_ ModeA2;

