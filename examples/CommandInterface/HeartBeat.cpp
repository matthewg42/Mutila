#include <Arduino.h>
#include "HeartBeat.h"

#if defined(ARDUINO_ESP8266_NODEMCU) 
Heartbeat HeartBeat(LED_BUILTIN, true); 
#else
Heartbeat HeartBeat(LED_BUILTIN); 
#endif

