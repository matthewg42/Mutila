#include <EMASonicRanger.h>
#include <Millis.h>
#include <MutilaDebug.h>
#include "TestBoardPins.h"

EMASonicRanger Ranger(HCSR01TriggerPin, HCSR01EchoPin);

// How often to print output
const uint16_t OutputPeriodMs = 100;
// Keep track of the last time we printed output
millis_t LastOutputMs = 0;

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    // Initialize our sonic ranger object
    Ranger.begin();

    Serial.println("setup() end");
}

void loop()
{
    // Give the ranger a timeslice to do sampling
    Ranger.update();

    // Print output every so often
    if (DoEvery(OutputPeriodMs, LastOutputMs)) {
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" range=");
        Serial.println(Ranger.getRange());
    }
}

