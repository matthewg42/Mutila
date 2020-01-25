#include <Arduino.h>
#include <MutilaDebug.h>
#include <SonicRanger.h>
#include <Millis.h>
#include "TestBoardPins.h"

SonicRanger Ranger(HCSR01TriggerPin, HCSR01EchoPin);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show we can handle Millis wrap
    AddMillisOffset(0xFFFFF000);

    // Initialize our ranger
    Ranger.begin();

    Serial.println("setup() end");
}

void loop()
{
    // Get the range, and record time before and after to 
    // work out how long the getRange() call takes
    millis_t before = Millis();
    uint16_t cm = Ranger.getRange();
    millis_t after = Millis();

    Serial.print("Millis=0x");
    Serial.print(Millis(), HEX);
    Serial.print(" range = ");
    Serial.print(cm);
    Serial.print(" cm, took ");
    Serial.print(MillisSince(before, after));
    Serial.println("ms");

    delay(50);
}

