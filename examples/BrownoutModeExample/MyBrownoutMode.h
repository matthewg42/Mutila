#pragma once

#include <BrownoutMode.h>

class MyBrownoutMode : public BrownoutMode {
public:
    MyBrownoutMode(EMAVDivSampler& vSampler, const float vThreshLow, const float vThreshHigh);
    void enterBrownout();
    void exitBrownout();
    void modeUpdate();

};

