#pragma once

#include <Mode.h>

// ModeB_ prints a message to Serial every half a second
class ModeB_ : public Mode {
public:
    ModeB_();
    void begin();
    void modeStart();
    void modeStop();
    void modeUpdate();

private:
    unsigned int counter;

};

// A global object for this class, in the same style as the Arduino Serial object
extern ModeB_ ModeB;

