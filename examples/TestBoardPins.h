#pragma once

// Pins for the Mutila Test Rig

#include <stdint.h>
#include <Arduino.h>


#if defined(ARDUINO_ESP8266_NODEMCU) 
const uint8_t DfpmTxPin =   D7;
const uint8_t DfpmRxPin =   D6;
const uint8_t DfpmBusyPin = D5;
#else
const uint8_t DfpmTxPin =   6;
const uint8_t DfpmRxPin =   7;
const uint8_t DfpmBusyPin = 5;
#endif

