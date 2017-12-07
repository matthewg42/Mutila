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
    Serial.println("setup() complete");
}

void loop()
{
    Pot.update();
    PotReversed.update();

    if (DoEvery(OutputMs, LastDb)) {
        Serial.print("analog value=");
        Serial.print(analogRead(AnalogPin));
        Serial.print(" Pot.value()=");
        Serial.print(Pot.value());
        Serial.print(" PotReversed.value()=");
        Serial.println(PotReversed.value());
    }
}

