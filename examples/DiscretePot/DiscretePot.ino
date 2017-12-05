#include <Arduino.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include <DiscretePot.h>

const uint8_t AnalogPin = A7;
const uint16_t OutputMs = 50;

DiscretePot Pot(AnalogPin);

uint32_t LastDb = 0;

void setup()
{
    Serial.begin(115200);
    Pot.begin(0, 11, true);
    delay(300);
    DBLN("setup() complete");
}

void loop()
{
    Pot.update();
    if (MillisSince(LastDb) > OutputMs) {
        LastDb = Millis();
        DB("Pot.value()=");
        DBLN(Pot.value());
    }
}

