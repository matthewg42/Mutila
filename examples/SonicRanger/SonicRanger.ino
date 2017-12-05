#include <Arduino.h>
#include <MutilaDebug.h>
#include <SonicRanger.h>
#include <Millis.h>

const uint8_t TriggerPin = 3;
const uint8_t EchoPin = 4;

SonicRanger Ranger(TriggerPin, EchoPin);
uint32_t LastDb = 0;

void setup()
{
    Serial.begin(115200);
    Ranger.begin();
    delay(300);
    DBLN("setup() complete");
}

void loop()
{
    unsigned long before = Millis();
    uint16_t cm = Ranger.getRange();
    unsigned long after = Millis();
    DB("range = ");
    DB(cm);
    DB(" cm, took ");
    DB(MillisSince(before, after));
    DBLN("ms");
    delay(50);
}

