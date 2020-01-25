#include <Arduino.h>
#include "HeartBeat.h"
#include "TestBoardPins.h"

#if defined(ARDUINO_ESP8266_NODEMCU) 
Heartbeat HeartBeat(LedPin, true); 
#else
Heartbeat HeartBeat(LedPin); 
#endif

