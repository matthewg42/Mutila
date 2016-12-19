#pragma once

#include <stdint.h>
#include <EMASampler.h>

/*! \brief Exponential Moving Average current sampler
 *
 * Sampler a current, EMA method.
 */
class EMACurrentSampler : public EMASampler {
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
    EMACurrentSampler(const uint8_t pin, 
                      const float vSupply, 
                      const float vRef,
                      const float iOffset, 
                      const uint16_t periodMs,
                      const float alpha);

    //! Get the mean value in the sample set
    virtual float averageAmps();

    //! Get the most recent voltage value
    virtual float lastAmps();

protected:
    float _vSupply;
    float _vRef;
    float _iOffset;

};

