#include <Arduino.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include <DiscretePot.h>

const uint8_t AnalogPin = A0;
const uint16_t OutputMs = 100;

uint32_t LastDb = 0;
DiscretePot Pot(AnalogPin);

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
    if (DoEvery(OutputMs, LastDb)) {
        DB("Pot.value()=");
        DBLN(Pot.value());
    }
}

