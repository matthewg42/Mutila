#pragma once

#include <stdint.h>


/*! Ringbuffer-based sampler for analog values
 *
 * This class keeps some number of samples in a ring buffer, enabling 
 * calculation of minimum, maximum, mean and count of samples in that
 * buffer
 */
class AnalogSampler {
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

    //! Accessor for the pin which is geting read from
    const uint8_t pin() { return _pin; }

    //! Get count of samples in buffer
    int count() { return _count; } 

    //! Get the minimum
    int minimum() { calculate(); return _min; }

    //! Get the maximum
    int maximum() { calculate(); return _max; }

    //! Get the average (mean)
    float mean() { calculate(); return _mean; }

    //! Get the most recent sample
    int last();

private:
    uint8_t _pin;               //!< pin to read data from
    uint8_t _samples;           //!< max number of samples
    uint16_t _periodMs;         //!< minimum ms
    unsigned long _lastUpdated; //!< when last sample taken
    int * _sampleData;          //!< ring buffer for data
    uint8_t _count;             //!< number of samles in _sampleData
    uint8_t _idx;               //!< index ptr (ring buffer)
    bool _updated;              //!< flag to re-calulate avg or not
    int _min;                   //!< store last calulated value
    int _max;                   //!< store last calulated value
    float _mean;                  //!< store last calulated value

    void calculate();           //!< calculate avg, min, max if required

};

