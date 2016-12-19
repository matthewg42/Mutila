#include <Arduino.h>
#include "DiscretePot.h"

#define ANALOG_PIN  A0
#define OUTPUT_MS   50

DiscretePot dPot(ANALOG_PIN);

unsigned long next = OUTPUT_MS;

void setup()
{
    Serial.begin(115200);
    dPot.begin(0, 11, true);
    delay(300);
    Serial.println("setup end");
}

void loop()
{
    dPot.update();
    if (millis() > next) {
        next = millis() + OUTPUT_MS;
        Serial.print("dPot.value()=");
        Serial.println(dPot.value());
    }
}

