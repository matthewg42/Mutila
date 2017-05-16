#pragma once

#include <stdint.h>
#include "SonicRanger.h"

/*! \brief Sonic ranger which does some averaging using the EMA method
 */
class EMASonicRanger : public SonicRanger {
public:
    /*! Constructor */
    EMASonicRanger(const uint8_t trigPin, const uint8_t echoPin, const uint16_t periodMs=10, const float alpha=0.5);
    /*! Initialization */
    void begin();
    /* Update the ranger (get range from hardware) */
    void update();
    /* Get the averaged range in cm */
    uint16_t getRange();

private:
    uint16_t _periodMs;         //!< how often we will fetch from hw
    float _alpha;               //!< alpha value used in EMA calculation
    unsigned long _lastUpdated; //!< when last sample taken
    float _movingAverage;       //!< most recently calculated mean value
    uint16_t _lastSample;       //!< keep the most recent sample
    
};

