#pragma once

#include <stdint.h>
#include "DebouncedButton.h"

/*! MultiThrowSwitch
 *
 *  For modelling things like rotary dials which can have one (or none) 
 *  of a group of pins active at a given time, with a numeric position
 *  between 1 and the number of throws for the position of the switch.
 *
 */
class MultiThrowSwitch {
public:
    /*! Constructor.
     *
     * \param throws the number of throws (pins) for the switch.
     * \param pins an array of pins (must be "throws" long).
     * \patam sticky if true, stay with the last active position
     *        until a new position is active. If false then
     *        the position is 0 if no pins are active.
     * \param pullup sets the logic type for the various pins.
     *
     * Note: if pullup is true the logic of the button is
     * inverted - i.e. when the pin in pulled to ground, the
     * button is considered to be pushed/on. The default is
     * pullup, meaning that a LOW state on the pin means
     * the button is on. Whilst this is a bit counter-intuitive,
     * it is preferred as a floating pin will revert to off
     * more readily than with non-pullup logic.
     */
    MultiThrowSwitch(uint8_t throws, const uint8_t pins[], bool sticky=false, bool pullup=true);

	/* Destructor.
	 *
	 * Will delete dynamically allocated DebouncedButton objects 
	 */
	virtual ~MultiThrowSwitch();

    /*! Initialization.
     *
     * \param startPosition which position is active at start (0 means automatic)
     * \param threshold how many tests of the pin must match for a press detection.
     * \param delay number of ms between tests of press detection.
     *
     * Should be called from setup(), or at any rate, before
     * other members are called. This will set the pinMode. The
     * minimum time it takes for button presses / released to register
     * is threshold * delay.
     */
    void begin(int startPosition=0, uint8_t threshold=AbstractDebouncedButton::DefaultThreshold, uint8_t delay=AbstractDebouncedButton::DefaultButtonDelay);

    /*! Allocate Timeslice.
     *
     * This method must be called frequently - usually from loop().
     */
    void update();

    /*! Get switch position.
     *
     * \return the lowest active pin as a number between 1 and the number of
     *         throws. If the object was constructed with the sticky parameter
     *         set, the last active pin is remembered, even if no pins are 
     *         active when position() is called. If not pins are active and the
     *         sticky property was not set, this method returns 0.
     */
    uint8_t position();

private:
	uint8_t _throws;
	bool _sticky;
    DebouncedButton** _buttons;
	uint8_t _pos;

};

