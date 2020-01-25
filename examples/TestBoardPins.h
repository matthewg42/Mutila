#pragma once

// Pins for the Mutila Test Rig

#include <stdint.h>
#include <Arduino.h>

#if defined(ARDUINO_ESP8266_NODEMCU) 
// Note: D4 is LED_BUILTIN for the NodeMCU.
const uint8_t Button1Pin        = D2;
const uint8_t Button2Pin        = D1;
const uint8_t Button3Pin        = D8;
const uint8_t AnalogButtonPin   = D0;
const uint8_t LedPin            = LED_BUILTIN;
const uint8_t DfpmTxPin         = D7;
const uint8_t DfpmRxPin         = D6;
const uint8_t DfpmBusyPin       = D5;
const uint8_t HCSR01EchoPin     = D0;
const uint8_t HCSR01TriggerPin  = D3;
#else
const uint8_t Button1Pin        = 3;
const uint8_t Button2Pin        = 2;
const uint8_t Button3Pin        = 4;
const uint8_t AnalogButtonPin   = A5;
const uint8_t LedPin            = LED_BUILTIN;
const uint8_t DfpmTxPin         = 6;
const uint8_t DfpmRxPin         = 7;
const uint8_t DfpmBusyPin       = 5;
const uint8_t HCSR01EchoPin     = 8;
const uint8_t HCSR01TriggerPin  = 9;
#endif

// Some aliases for other pins
const uint8_t VoltagePin        = AnalogButtonPin;

