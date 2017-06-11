#pragma once

#include <ParentMode.h>

class ModeA_ : public ParentMode {
public:
    ModeA_();
    void begin();
    void modeStart();
    void modeStop();
    void modeUpdate();

};

// A global object for this class, in the same style as the Arduino Serial object
extern ModeA_ ModeA;

