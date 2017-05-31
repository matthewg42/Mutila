#pragma once

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

    /*! Constructor
     * \param pin the pin connected to the indicator LED (13 is a good
     *        value on many boards as the build-in LED is usually attached
     *        to this pin
     */
	Heartbeat(int pin);
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

    /*! Set custom flashing timing
     * \param onTime how long the LED stays on in ms
     * \param offTime how long the LED stays off in ms
     */
    void setCustomMode(uint16_t onTime, uint16_t offTime);

    /* Timeslice allocation
     * should be called frequently - usually from the loop() function in your sketch.
     */
	void update();

private:
    void updatePin(bool state);

	Mode _mode;
	int _pin;
	bool _pinState;
	unsigned long _lastStateFlip;
	unsigned int _onTime;
	unsigned int _offTime;

};

