#include <Arduino.h>
#include <DiscretePot.h>
#include <Millis.h>
#include <MutilaDebug.h>

#define ANALOG_PIN  A0
#define OUTPUT_MS   50

DiscretePot dPot(ANALOG_PIN);

unsigned long next = OUTPUT_MS;

void setup()
{
    Serial.begin(115200);
    dPot.begin(0, 11, true);
    delay(300);
    DBLN("setup() complete");
}

void loop()
{
    dPot.update();
    if (Millis() > next) {
        next = Millis() + OUTPUT_MS;
        DB("dPot.value()=");
        DBLN(dPot.value());
    }
}

