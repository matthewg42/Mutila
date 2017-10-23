#pragma once

#include <stdint.h>

/*! \brief LED flashing status indicator
 * The Heartbeat class flashes an LED periodically to indicate
 * the state of the system.  A Heartbeat can be set to one of several
 * modes, which changes the rate of flashing to indicate different
 * firmware states.
 */
class Heartbeat {
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

    /*! Constructor
     * \param pin the pin connected to the indicator LED (13 is a good
     *        value on many boards as the build-in LED is usually attached
     *        to this pin
     * \param invertedLogic invert the logic of the pin (useful for using D0
     *        on the ESP8266, which has inverted logic)
     */
	Heartbeat(int pin, bool invertedLogic=false);
	~Heartbeat();

    /*! Initialization
     * Should be called from setup() - sets the pin mode.
     */
    void begin();

    /*! get current flashing mode */
    Mode mode();

    /*! Set flashing mode
     * \param mode the new mode to use
     */
	void setMode(Mode mode);

    /*! Set flashing mode
     * \param times retrieved from the times() call.
     * The if times.mode is not Custom, setMode(Mode) will be used to set the
     * on and off times, else setCustomMode() will be called with the values
     * from times.
     */
    void setMode(Times times);

    /*! Set custom flashing timing
     * \param onTime how long the LED stays on in ms
     * \param offTime how long the LED stays off in ms
     */
    void setCustomMode(uint16_t onTime, uint16_t offTime);

    /* Timeslice allocation
     * should be called frequently - usually from the loop() function in your sketch.
     */
	void update();

    /*! Turn on/off the heartbeat. Over-rides setMode()
     */
    void setEnabled(bool on=true);

    /* Get current on and off times. This can theb 
     */
    Times times();

private:
    void updatePin(bool state);

	Mode _mode;
	int _pin;
	bool _pinState;
	unsigned long _lastStateFlip;
	unsigned int _onTime;
	unsigned int _offTime;
    bool _invertedLogic;
    bool _enabled;

};

