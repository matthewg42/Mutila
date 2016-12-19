#pragma once

#include <stdint.h>
#include <EMASampler.h>

/*! Exponential Moving Average Voltage Divider based voltage sampler
 *
 * Sampler a voltage using a voltage divider, EMA method.
 */
class EMAVDivSampler : public EMASampler {
public:
    /*! Constructor
     * \param pin the analog input pin to read samples from
     * \param periodMs the number of milliseconds between samples.  If update() is called
     *        before periodMs has passed since the last update(), no sample will be taken.
     * \param samples the number of samples to keep in the ring buffer used to calculate
     *        average(), minimum() and maximum().
     *
     * Note: this class dynamically allocated memory for the ring buffer.
     */
    EMAVDivSampler(const uint8_t pin, 
                   const uint16_t r1KOhm, 
                   const uint16_t r2KOhm, 
                   const float vRef,
                   const uint16_t periodMs,
                   const float alpha);

    //! Get the mean value in the sample set
    virtual float averageVolts();

    //! Get the most recent voltage value
    virtual float lastVolts();

protected:
    uint16_t _r1KOhm;
    uint16_t _r2KOhm;
    float _vRef;

};

