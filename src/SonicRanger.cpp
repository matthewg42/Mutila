#include <Arduino.h>
#include <Millis.h>
#include "SonicRanger.h"

#ifdef ARDUINO_AVR_DIGISPARK
// Implementation missing when building for DigiSpark, so I copy-pasted it from:
// https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/cores/arduino/wiring_pulse.c#L63
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout)
{
	// cache the port and bit of the pin in order to speed up the
	// pulse width measuring loop and achieve finer resolution.  calling
	// digitalRead() instead yields much coarser resolution.
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	uint8_t stateMask = (state ? bit : 0);

	unsigned long startMicros = micros();

	// wait for any previous pulse to end
	while ((*portInputRegister(port) & bit) == stateMask) {
		if (micros() - startMicros > timeout)
			return 0;
	}

	// wait for the pulse to start
	while ((*portInputRegister(port) & bit) != stateMask) {
		if (micros() - startMicros > timeout)
			return 0;
	}

	unsigned long start = micros();
	// wait for the pulse to stop
	while ((*portInputRegister(port) & bit) == stateMask) {
		if (micros() - startMicros > timeout)
			return 0;
	}
	return micros() - start;
}
#endif // ARDUINO_AVR_DIGISPARK

SonicRanger::SonicRanger(const uint8_t trigPin, const uint8_t echoPin) :
    _trigPin(trigPin),
    _echoPin(echoPin),
    _maxCm(SONIC_RANGE_DEFAULT_MAX_CM),
    _timeoutMs(SONIC_RANGE_DEFAULT_TIMEOUT_MS)
{
}

void SonicRanger::begin()
{
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

uint16_t SonicRanger::getRange()
{
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    unsigned long b4 = Millis();
    digitalWrite(_trigPin, LOW);
    unsigned long time = pulseInLong(_echoPin, HIGH, _timeoutMs*1000UL);
    unsigned long after = Millis();
    if (after - b4 >= _timeoutMs) {
        return _maxCm;
    } else {
        return time*0.034/2;
    }
}

