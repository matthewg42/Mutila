#pragma once

#include <stdint.h>
#include <AbstractSampler.h>

/*! Ringbuffer-based sampler for analog values
 *
 * This class keeps a fixed number of samples in a ring buffer, enabling 
 * calculation of minimum(), maximum(), average() (mean) values. 
 *
 * Advantages:
 *   - calculates actual mean value for samples in buffer
 *   - provides minimum() and maximum() values for values in buffer
 *
 * Disadvantages:
 *   - memory usage increases with number of samples
 *   - takes longer to calculate than exponential moving average
 */
class BufferedSampler : public AbstractSampler {
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
    BufferedSampler(const uint8_t pin, const uint16_t periodMs=10, const uint8_t samples=10);

    /*! Destructor
     *
     * Destroy the BufferedSampler, and free memory used for the ring buffer.
     */
    ~BufferedSampler();

    /*! Initialization
     * Should be called before the object is used, and may also be
     * called at any other time to clear the ring buffer.  Immediately after
     * begin() is called, average(), minimum() and maximum() will return 0.
     */
    virtual void begin();

    /*! Time slice allocation
     * This method should be called every time a sample is to be taken. If the 
     * BufferedSampler object was constucted with periodMs > 0, this method will
     * only add a new sample to the ring buffer if at least periodMs milliseconds
     * has elapsed since the last call to update().
     */
    virtual void update();

    //! The minimum value in the sample set
    virtual int minimum() { calculate() ; return _min; }

    //! The maximum value in the sample set
    virtual int maximum() { calculate() ; return _max; }

    //! Get the mean value in the sample set
    virtual float average() { calculate() ; return _mean; }

    /*! Sample count
     * The number of samples currently held in the ring buffer which are
     * being used to calculate the average, minimum, maximum values. This
     * will be 0 after the BufferedSampler has been constructed or begin()
     * called, and will rise by 1 each time a sample is taken until the 
     * maximum number of samples is reached.
     */
    virtual uint8_t count() { return _count; }

    //! Get the most recent sample value
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
    float _mean;                //!< most recently calculated mean value

};

