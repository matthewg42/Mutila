#pragma once

#include <stdint.h>
#include <AbstractSampler.h>

/*! Exponential Moving Average (EMA) Sampler class
 *
 * This sampler is used to calculate the exponential moving average for the
 * analog values read from a pin. This method can be used to smooth a value over
 * a large number of samples without having to use a lot of memory maintaining
 * a buffer of recent values sampled from the pin, and should also be faster
 * to calculate than the method used in the BufferedSampler approach. However, 
 * the user should be aware that the exponential moving average value is not
 * the same as the mean value over a discrete set of samples (although it
 * can often be used in situaltions where the mean may also be used).
 *
 * Advantages:
 *   - smoothing over long periods with low memory usage (low alpha values)
 *   - effificient, constant time calculation of moving average
 *   - responds faster to change than BufferedSampler
 *
 * Disadvantages:
 *   - not mean or median average (see link below)
 *   - longer "tail" effect than BufferedSampler
 *
 * See also: https://en.wikipedia.org/wiki/Moving_average#Exponential_moving_average
 */
class EMASampler : public AbstractSampler {
public:
    /*! Constructor
     * \param pin the analog pin to read samples from
     * \param periodMs the minimum gap between taking samples
     * \param alpha for determining number of samples to smooth over 
     *        (between 0 and 1 - a higher alpha discounts older samples 
     *        faster).
     */
    EMASampler(const uint8_t pin, const uint16_t periodMs=10, const float alpha=0.5);

    //! Destructor
    ~EMASampler() {;}

    /*! Initialization
     * Should be called before use, and may also be called at any time to clear the
     * moving average value. Note the moving average will be set to 0 when begin()
     * in called.
     */
    virtual void begin();

    /*! Time slice allocation
     * This method should be called every time a sample is to be taken. 
     * If the object was constucted with periodMs > 0, this method will
     * only take into account a new sample if at least periodMs milliseconds
     * has elapsed since the last call to update().
     */
    virtual void update();

    //! The mean value in the sample set
    virtual float average() { return _movingAverage; }

    //! Get the most recent sample
    virtual int last() { return _lastSample; }

protected:
    float _alpha;               //!< alpha value used in EMA calculation
    unsigned long _lastUpdated; //!< when last sample taken
    float _movingAverage;       //!< most recently calculated mean value
    int _lastSample;            //!< keep the most recent sample

};

