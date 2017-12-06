#include <Arduino.h>
#include <MutilaDebug.h>
#include <SonicRanger.h>
#include <Millis.h>

const uint8_t TriggerPin = 3;
const uint8_t EchoPin = 4;

SonicRanger Ranger(TriggerPin, EchoPin);

void setup()
{
    Serial.begin(115200);
    Ranger.begin();
    // Show we can handle Millis wrap
    addMillisOffset(0xFFFFF000);
    delay(300);
    DBLN("setup() complete");
}

void loop()
{
    unsigned long before = Millis();
    uint16_t cm = Ranger.getRange();
    unsigned long after = Millis();

    DB("Millis=0x");
    DB(Millis(), HEX);
    DB(" range = ");
    DB(cm);
    DB(" cm, took ");
    DB(MillisSince(before, after));
    DBLN("ms");

    delay(50);
}

