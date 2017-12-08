#pragma once

#include <stdint.h>
#include <Arduino.h>

#if defined(ARDUINO_ESP8266_NODEMCU) 
const uint8_t ButtonAPin = D1;
const uint8_t ButtonBPin = D2;
#else
const uint8_t ButtonAPin = 6;
const uint8_t ButtonBPin = 5;
#endif

