#include <Arduino.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include <DiscretePot.h>

const uint8_t AnalogPin = A0;
const uint16_t OutputMs = 100;

uint32_t LastDb = 0;
DiscretePot Pot(AnalogPin);
DiscretePot PotReversed(AnalogPin);

void setup()
{
    Serial.begin(115200);
    Pot.begin(0, 10);
    PotReversed.begin(0, 10, true);
    delay(300);
    DBLN("setup() complete");
}

void loop()
{
    Pot.update();
    PotReversed.update();

    if (DoEvery(OutputMs, LastDb)) {
        DB("analog value=");
        DB(analogRead(AnalogPin));
        DB(" Pot.value()=");
        DB(Pot.value());
        DB(" PotReversed.value()=");
        DBLN(PotReversed.value());
    }
}

