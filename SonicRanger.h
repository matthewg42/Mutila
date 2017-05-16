#pragma once

#include <stdint.h>

/*! \brief Class for using HC-SR04 Ultrasonic ranging devices
 */

class SonicRanger {
public:
    /*! Constructor */
    SonicRanger(const uint8_t trigPin, const uint8_t echoPin);
    /*! Initialization */
    void begin();
    /*! Get range in cm */
    uint16_t getRange();

private:
    uint8_t _trigPin;
    uint8_t _echoPin;

};

