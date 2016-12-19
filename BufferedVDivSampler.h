#pragma once

#include <stdint.h>
#include <BufferedSampler.h>

/*! Buffered voltage divider based voltage sampler
 *
 * Sampler a voltage using a voltage divider, buffering values.
 */
class BufferedVDivSampler : public BufferedSampler {
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
    BufferedVDivSampler(const uint8_t pin, 
                        const uint16_t r1KOhm, 
                        const uint16_t r2KOhm, 
                        const float vRef=5.0,
                        const uint16_t periodMs=10, 
                        const uint8_t samples=10);

    //! Get the mean value in the sample set
    virtual float averageVolts();

    //! Get the most recent voltage value
    virtual float lastVolts();

protected:
    uint16_t _r1KOhm;
    uint16_t _r2KOhm;
    float _vRef;

};

