#pragma once

// Pins for the Mutila Test Rig

#include <stdint.h>
#include <Arduino.h>

#if defined(ARDUINO_ESP8266_NODEMCU) 
const uint8_t Button1Pin        = D1;
//const uint8_t Button2Pin        = ;
//const uint8_t Button3Pin        = ;
//const uint8_t AnalogButtonPin   = ;
//const uint8_t LedPin            = ;
const uint8_t DfpmTxPin         = D7;
const uint8_t DfpmRxPin         = D6;
const uint8_t DfpmBusyPin       = D5;
//const uint8_t HCSR01TriggerPin  = ;
//const uint8_t HCSR01EchoPin     = ;
#else
const uint8_t Button1Pin        = 3;
const uint8_t Button2Pin        = 2;
const uint8_t Button3Pin        = 4;
const uint8_t AnalogButtonPin   = A5;
const uint8_t LedPin            = LED_BUILTIN;
const uint8_t DfpmTxPin         = 6;
const uint8_t DfpmRxPin         = 7;
const uint8_t DfpmBusyPin       = 5;
const uint8_t HCSR01TriggerPin  = 9;
const uint8_t HCSR01EchoPin     = 8;
#endif

// Some aliases for other pins
const uint8_t VoltagePin        = AnalogButtonPin;

