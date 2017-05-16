#pragma once

#include <stdint.h>

/*! \brief HC-SR04 Ultrasonic ranger device
 *
 * SonicRanger provides a simple wrapper around the calculation 
 * necessary to determine the range of an object using a HC-SR04
 * ultrasonic range finder.
 *
 */

class SonicRanger {
public:
    /*! Constructor 
     *
     * \param trigPin the arduino pin conneced to the TRIG pin of the HC-SR04 device
     * \param echoPin the arduino pin conneced to the ECHO pin of the HC-SR04 device
     */
    SonicRanger(const uint8_t trigPin, const uint8_t echoPin);
    /*! Initialization
     *
     * Typically called from setup() 
     */
    void begin();
    /*! Get range in cm 
     *
     * Return the range of the nearest object to the HC-SR04
     * device. 
     *
     * If no object is in range, some high value like 2975 or
     * 3000 will be returned.
     *
     * NOTE: execution time depends on the range to an object.
     * Of no object is in range, the execution time can be 
     * quite significant!
     *
     * Range=10cm, execution time=1ms
     * Range=100cm, execution time=6ms
     * Range=3000cm, execution time=180ms
     */
    uint16_t getRange();

private:
    uint8_t _trigPin;
    uint8_t _echoPin;

};

