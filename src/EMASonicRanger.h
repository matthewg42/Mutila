#pragma once

#include <stdint.h>
#include <Millis.h>
#include <SonicRanger.h>

/*! \brief SonicRanger with EMA-smoothed values
 *
 * The update() function should be called frequently to sample
 * the value from the ranger. The getRange() function is then
 * used to fetch the moving average of values from the ranger.
 *
 */
class EMASonicRanger : public SonicRanger {
public:
    /*! Constructor.
     *
     * \param trigPin the arduino pin conneced to the TRIG pin of the HC-SR04 device
     * \param echoPin the arduino pin conneced to the ECHO pin of the HC-SR04 device
     * \param periodMs the minimum delay between sampling (provided update() is called)
     * \param alpha the alpha value used in EMA calculation
     * \param minimumRange the minium range to try to detect (discard samples below this range)
     *
     * The reason for the mimimum range is that some units exhibit a problem where they randomly 
     * report skewing results.
     */
    EMASonicRanger(const uint8_t trigPin, const uint8_t echoPin, const millis_t periodMs=10, const float alpha=0.5, const uint16_t minimumRange=3);

    /*! Initialization 
     * 
     * Typically called from setup() to intialize pins and so on.
     */
    void begin();

    /*! Update the ranger (get range from hardware) 
     *
     * NOTE: this function calls SonicRanger::getRange(), which may
     * take significant time to execute - see SonicRanger::getRange
     * documentation for details.
     */
    void update();
    
    /*! Fetch exponential moving average
     *
     */
    uint16_t getRange();

private:
    millis_t _periodMs;         //!< how often we will fetch from hw
    float _alpha;               //!< alpha value used in EMA calculation
    millis_t _lastUpdated;      //!< when last sample taken
    float _movingAverage;       //!< most recently calculated mean value
    uint16_t _lastSample;       //!< keep the most recent sample
    uint16_t _minimumRange;     //!< set to non-0 to discard samples below minimum
    
};

