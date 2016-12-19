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
class BufferedSampler : public AbstractSampler {
public:
    /*! Constructor
     * Note: This class dynamically allocates memory for the sample buffer
     */
    BufferedSampler(const uint8_t pin, const uint8_t samples, const uint16_t periodMs);

    //! Destructor
    ~BufferedSampler();

    //! Initialization
    virtual void begin();

    //! Time slice allocation
    virtual void update();

    //! The minimum value in the sample set
    virtual int minimum() { calculate() ; return _min; }

    //! The maximum value in the sample set
    virtual int maximum() { calculate() ; return _max; }

    //! The mean value in the sample set
    virtual float average() { calculate() ; return _average; }

    //! Sample count
    //! The number of samples currently held in the sample buffer which are
    //! being used to calculate the average, minimum, maximum values. This
    //! will be 0 after the BufferedSampler has been constructed, and will rise
    //! by 1 each time a sample is taken until the maximum number of samples
    //! is reached, where it will stay.
    virtual uint8_t count() { return _count; }

    //! Get the most recent sample
    virtual int last();

protected:
    virtual void calculate();   //!< calculate avg, min, max if required

    uint8_t _samples;           //!< max number of samples to keep in buffer
    uint8_t _idx;               //!< index ptr (ring buffer)
    uint8_t _count;             //!< number of samples in buffer
    unsigned long _lastUpdated; //!< when last sample taken
    bool _updated;              //!< flag to re-calulate avg or not
    int * _sampleData;          //!< ring buffer for data
    int _min;                   //!< most recently calculated minimum value
    int _max;                   //!< most recently calculated maximum value
    float _average;             //!< most recently calculated mean value

};

