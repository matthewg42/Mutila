#pragma once

#include <ParentMode.h>

class ModeAClass : public ParentMode {
public:
    ModeAClass();
    void begin();
    void modeStart();
    void modeStop();
    void modeUpdate();

};

// A global object for this class, in the same style as the Arduino Serial object
extern ModeAClass ModeA;

