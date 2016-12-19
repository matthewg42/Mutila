#pragma once

#include <stdint.h>
#include <AbstractSampler.h>

/*! Ringbuffer-based sampler for analog values
 *
 * This class keeps some number of samples in a ring buffer, enabling 
 * calculation of minimum, maximum, mean and count of samples in that
 * buffer.  This becomes memory-inefficient when large numbers of
 * samples are required.
 */
class AnalogSampler : public AbstractSampler {
public:
    /*! Constructor
     * Note: This class dynamically allocates memory for the sample buffer
     */
    AnalogSampler(const uint8_t pin, const uint8_t samples, const uint16_t periodMs);

    //! Destructor
    ~AnalogSampler();

    //! Initialization
    void begin();

    //! Time slice allocation
    void update();

    //! Get the most recent sample
    int last();

protected:
    void calculate();           //!< calculate avg, min, max if required

    uint8_t _idx;               //!< index ptr (ring buffer)
    unsigned long _lastUpdated; //!< when last sample taken
    bool _updated;              //!< flag to re-calulate avg or not
    int * _sampleData;          //!< ring buffer for data

};

