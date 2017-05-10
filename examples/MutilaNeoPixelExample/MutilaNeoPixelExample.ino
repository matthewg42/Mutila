#include <Arduino.h>
#include <MutilaDebug.h>
#include <MutilaNeoPixel.h>
#include <Millis.h>

#define DEBUG_OUTPUT_MS     500
#define NEOPIXEL_UPDATE_MS  10
#define NEOPIXEL_TYPE       (NEO_GRB + NEO_KHZ800)
#define NEOPIXEL_PIN        3
#define NEOPIXEL_LEDS       200

MutilaNeoPixel leds(NEOPIXEL_LEDS, NEOPIXEL_PIN, NEOPIXEL_TYPE);

unsigned long nextDebug = DEBUG_OUTPUT_MS;
unsigned long nextLedUpdate = NEOPIXEL_UPDATE_MS;
unsigned int updateCount = 0;

void setup()
{
    Serial.begin(115200);
    leds.begin();
    delay(200);
    DBLN("setup() complete");
}

void loop()
{
    if (Millis() > nextLedUpdate) {
        updateCount++;
        leds.show();
    }

    if (Millis() > nextDebug) {
        nextDebug = Millis() + DEBUG_OUTPUT_MS;
        unsigned long M = Millis();
        unsigned long m = millis();
        unsigned long d = Millis() - millis();
        DB("Millis()=");
        DB(M);
        DB(" millis()=");
        DB(m);
        DB(" updateCount=");
        DB(updateCount);
        DB(" drift=");
        DBLN(M-m);
    }
}


