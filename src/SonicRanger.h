#pragma once

#include <stdint.h>
#include "Millis.h"

/*! HC-SR04 Ultrasonic ranger device
 *
 *  SonicRanger provides a simple wrapper around the calculation 
 *  necessary to determine the range of an object using a HC-SR04
 *  ultrasonic range finder.
 *
 */

#ifdef ARDUINO_AVR_DIGISPARK
micros_t pulseInLong(uint8_t pin, uint8_t state, micros_t timeout);
#endif // ARDUINO_AVR_DIGISPARK

class SonicRanger {
public:
    static const uint16_t DefaultMaxRangeCm = 200;
    static const uint8_t DefaultTimeoutMs = 15;

public:
    /*! Constructor.
     *
     *  \param trigPin the arduino pin conneced to the TRIG pin of the HC-SR04 device.
     *  \param echoPin the arduino pin conneced to the ECHO pin of the HC-SR04 device.
     */
    SonicRanger(const uint8_t trigPin, const uint8_t echoPin);
    /*! Initialization.
     *
     *  Typically called from setup().
     */
    void begin();
    /*! Get range in cm.
     *
     *  \return the range of the nearest object to the HC-SR04
     *          device in cm (approximate). If no object is in range, 
     *          some the maximum range (200 cm) will be returned.
     *
     *  NOTE: execution time depends on the range to an object.
     *  Of no object is in range, the ranging will time out after
     *  15ms. The maximum range and timeout values can be set
     *  using setMaxRange() and setTimeoutMs().
     *
     *  Range=10cm, execution time ~1 ms
     *  Range=50cm, execution time ~4 ms
     *  Range=100cm, execution time ~7 ms
     *  Range=150cm, execution time ~10 ms
     *  Range=>200cm, execution time ~15 ms
     */
    uint16_t getRange();

    /*! Set maximum range
     *
     *  \param cm the new maximum range in cm.
     */
    void setMaxRange(uint16_t cm) { _maxCm = cm; }

    /*! Set timeout in ms.
     *
     *  \param ms the new timeout in milliseconds.
     *
     *  Note that you need to allow about 7 ms for every 100
     *  cm of range you wish to be able to measure. Typically
     *  HC-SR04 units can only reliably measure ranges of up
     *  a couple of meters. 
     */
    void setTimeoutMs(uint16_t ms) { _timeoutMs = ms; }

private:
    const uint8_t _trigPin;
    const uint8_t _echoPin;
    uint16_t _maxCm;
    uint16_t _timeoutMs;

};

