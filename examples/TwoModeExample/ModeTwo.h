#pragma once

#include <Mode.h>

// ModeTwo_ prints a message to Serial every half a second
// ModeTwo_ terminated when ButtonA is pushed.
class ModeTwo_ : public Mode {
public:
    ModeTwo_();
    void start();
    void stop();
    void update();
    bool isFinished();

private:
    unsigned long _last;
    unsigned long _start;

};

// A global object for this class, in the same style as the Arduino Serial object
extern ModeTwo_ ModeTwo;

