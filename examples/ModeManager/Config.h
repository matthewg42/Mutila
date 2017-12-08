#pragma once

#include <stdint.h>
#include <Arduino.h>

#if defined(ARDUINO_ESP8266_NODEMCU) 
const uint8_t ButtonPin = D1;
#else
const uint8_t ButtonPin = 6;
#endif

