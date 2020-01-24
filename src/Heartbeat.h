#pragma once

#include <stdint.h>
#include "Millis.h"

/*! LED flashing status indicator.
 *
 *  The Heartbeat class flashes an LED periodically to indicate
 *  the state of the system.  A Heartbeat can be set to one of several
 *  modes, which changes the rate of flashing to indicate different
 *  firmware states.
 */
class Heartbeat {
public:
    static const uint16_t NormalOnMs =      50;
    static const uint16_t NormalOffMs =     450;
    static const uint16_t QuickOnMs =       25;
    static const uint16_t QuickOffMs =      125;
    static const uint16_t QuickerOnMs =     25;
    static const uint16_t QuickerOffMs =    25;
    static const uint16_t SlowOnMs =        50;
    static const uint16_t SlowOffMs =       950;
    static const uint16_t SlowerOnMs =      50;
    static const uint16_t SlowerOffMs =     1950;

public:
    /*! Flashing mode */
	enum Mode {
		Normal=0, //!< blinks every 500ms
		Quick,    //!< blinks every 150ms
		Quicker,  //!< blinks every 50ms
		Slow,     //!< blinks every 1000ms
		Slower,   //!< blinks every 2000ms
        Off,      //!< LED constant off
        On,       //!< LED constant on
        Custom    //!< Indicates custom on/off times (set with setCustomMode)
	};

    typedef struct {
        Mode mode;
        uint16_t onTime;
        uint16_t offTime;
    } Times;

    /*! Constructor.
     *
     *  \param pin the pin connected to the indicator LED, often 13 for built-in
     *         LED.
     *  \param invertedLogic invert the logic of the pin (useful for using D0
     *         on the ESP8266, which has inverted logic).
     */
	Heartbeat(const uint8_t pin, const bool invertedLogic=false);
	~Heartbeat();

    /*! Initialization.
     *
     *  Should be called from setup() - sets the pin mode.
     */
    void begin();

    /*! Get current flashing mode.
     */
    Mode mode();

    /*! Set flashing mode.
     *
     *  \param mode the new mode to use.
     */
	void setMode(Mode mode);

    /*! Set flashing mode.
     *
     *  \param times retrieved from the times() call. 
     *
     *  If mode is not Custom, setMode(Mode) will be used to set the on 
     *  and off times, else setCustomMode() will be called with the values
     *  from times().
     */
    void setMode(Times times);

    /*! Set custom flashing timing.
     *
     *  \param onTime how long the LED stays on in ms.
     *  \param offTime how long the LED stays off in ms.
     */
    void setCustomMode(uint16_t onTime, uint16_t offTime);

    /*! Timeslice allocation.
     *
     *  Should be called frequently - usually from the loop() function in 
     *  your sketch.
     */
	void update();

    /*! Turn on/off the heartbeat. 
     * 
     *  Note: over-rides setMode()
     */
    void setEnabled(bool on=true);

    /*! Get current on and off times.
     */
    Times times();

private:
    void updatePin(bool state);

private:
	Mode _mode;
	const uint8_t _pin;
    const bool _invertedLogic;
	bool _pinState;
	millis_t _lastStateFlip;
	uint16_t _onTime;
	uint16_t _offTime;
    bool _enabled;

};

