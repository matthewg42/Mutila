#pragma once

#include "Mode.h"
#include "EMAVDivSampler.h"

/*! \brief Mode class with brownout detection
 *
 * A mode implementation with members which are called when some monitored
 * voltage drops below a low threshold or rises above a high threshold.  This
 * is typically used to save state to EEPROM when power is dying, or disable/
 * enable power-hungry activities if the voltage drops too low.
 */
class BrownoutMode : public Mode {
public:
    /*! Constructor
     * \param vSampler a EMAVDivSampler which will be used to test the brownout voltage
     * \param vThreshLow the low threshold voltage
     * \param vThreshHigh the high threshold voltage
     */
    BrownoutMode(EMAVDivSampler& vSampler, const float vThreshLow, const float vThreshHigh);

    /*! Allocate Timeslice
     * Should be called frequently - typically from loop()
     */
    virtual void update();

    /*! Brownout entry callback
     * This will be called once if the voltage measured by the sampler drops below the 
     * lower threshold.
     */
    virtual void enterBrownout() {;}

    /*! Brownout exit callback
     * This will be called once if the voltage measured by the sampler rises above the 
     * higher threshold.
     */
    virtual void exitBrownout() {;}

    /*! Test Brownout Status
     * \return true if device is currently browned out
     */
    const bool brownedOut() { return _brownedOut; }

protected:
    EMAVDivSampler& _vSampler;
    float _vThreshLow;
    float _vThreshHigh;
    bool _brownedOut;
};

