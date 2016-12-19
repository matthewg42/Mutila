#pragma once

#include <stdint.h>


/*! Base class for other sampling classes
 *
 */
class AbstractSampler {
public:
    /*! Constructor
     *
     * \param pin the analog reading pin to read data from
     * \param samples the number of samples to consider when calculating values
     * \param periodMs time between samples (set to 0 to sample ever time update() is called)
     */
    AbstractSampler(const uint8_t pin, const uint8_t samples, const uint16_t periodMs=0) : 
        _pin(pin), 
        _samples(samples), 
        _periodMs(periodMs), 
        _count(0), 
        _min(0), 
        _max(0), 
        _mean(0.) {;}

    //! Destructor
    virtual ~AbstractSampler() {;};

    //! Initialization
    //! Optionally implement in derived classes 
    virtual void begin() {;}

    //! Update samples
    //! Must be implemented in derived classes
    virtual void update() = 0;

    //! Accessor for the pin which is geting read from
    virtual const uint8_t pin() { return _pin; }

    //! Optionally override in derived classes
    virtual int count() { return _count; } 

    //! Optionally override in derived classes
    virtual int minimum() { calculate(); return _min; }

    //! Optionally override in derived classes
    virtual int maximum() { calculate(); return _max; }

    //! Optionally override in derived classes
    virtual float mean() { calculate(); return _mean; }

    //! Get the most recent sample
    virtual int last() = 0;

protected:
    //! Must implement this
    virtual void calculate() = 0;

    uint8_t _pin;               //!< pin to read data from
    uint8_t _samples;           //!< max number of samples
    uint16_t _periodMs;         //!< minimum ms
    uint8_t _count;             //!< number of samles in _sampleData
    int _min;                   //!< store last calulated value
    int _max;                   //!< store last calulated value
    float _mean;                  //!< store last calulated value

};

