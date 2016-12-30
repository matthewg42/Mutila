#include "BrownoutMode.h"

BrownoutMode::BrownoutMode(EMAVDivSampler& vSampler, const float vThreshLow, const float vThreshHigh) :
    _vSampler(vSampler),
    _vThreshLow(vThreshLow),
    _vThreshHigh(vThreshHigh),
    _brownedOut(true)
{
}

void BrownoutMode::update()
{
    _vSampler.update();
    _DB(F("Mode::update, volts="));
    _DBLN(_vSampler.averageVolts());
    if (_brownedOut && _vSampler.averageVolts() > _vThreshHigh) {
        exitBrownout();
        _brownedOut = false;
    } else if (!_brownedOut && _vSampler.averageVolts() < _vThreshLow) {
        enterBrownout();
        _brownedOut = true;
    }
    Mode::update();
}



