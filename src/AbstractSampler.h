#pragma once

#include <stdint.h>


/*! \brief Base class for analog pin sampling classes
 *
 * All samplers can calulate an averge value. The exact method of calculation
 * and type of average may vary depending on the derived class - see derived
 * class documentation for details.
 */
class AbstractSampler {
public:
    /*! Constructor
     *
     * \param pin the analog reading pin to read data from
     * \param periodMs time between samples (set to 0 to sample ever time update() is called)
     */
    AbstractSampler(const uint8_t pin, const uint16_t periodMs) : 
        _pin(pin), 
        _periodMs(periodMs) {;}

    //! Destructor
    virtual ~AbstractSampler() {;};

    //! Initialization
    //! Optionally implement in derived classes 
    virtual void begin() {;}

    //! Update - must be implemented in derived classes
    virtual void update() = 0;

    //! Accessor for the pin which is geting read from
    uint8_t pin() { return _pin; }

    //! Implement (and document!) in derived classes
    virtual float average() = 0;

    //! Get the most recent sample - derived classes must implement
    virtual int last() = 0;

protected:
    const uint8_t _pin;             //!< pin to read data from
    const uint16_t _periodMs;       //!< minimum ms

};

