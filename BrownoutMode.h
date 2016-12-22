#pragma once

#include "Mode.h"
#include "EMAVDivSampler.h"

class BrownoutMode : public Mode {
public:
    BrownoutMode(EMAVDivSampler& vSampler, const float vThreshLow, const float vThreshHigh);
    virtual void update();
    virtual void enterBrownout() {;}
    virtual void exitBrownout() {;}
    const bool brownedOut() { return _brownedOut; }

protected:
    EMAVDivSampler& _vSampler;
    float _vThreshLow;
    float _vThreshHigh;
    bool _brownedOut;
};

