#include <Arduino.h>
#include <MutilaDebug.h>
#include "TestCLI.h"
#include "HeartBeat.h"
#include "TestBoardPins.h"

#if defined(ARDUINO_ESP8266_NODEMCU) 
Heartbeat heartbeat(LedPin, true); 
#else
Heartbeat heartbeat(LedPin); 
#endif

// Function prototypes are useful when building with make, as they
// enable us to order the functions in the file in the order we choose
// instead of defining them before they are called.  This isn't needed
// if building with the IDE, or you don't care about the order of the
// functions in the file.
void setup();
void loop();

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Initialize our objects
    HeartBeat.begin();
    TestCLI.begin(Serial);

    // Suppress the usual infomation here, so we get our prompt unfettered...
    // Serial.println("setup() end");
}

void loop()
{
    // Give a timeslice to our objects
    HeartBeat.update();
    TestCLI.update();
}

