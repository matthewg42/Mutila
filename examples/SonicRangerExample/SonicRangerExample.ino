#include <Arduino.h>
#include <MutilaDebug.h>
#include <SonicRanger.h>
#include <Millis.h>

#define TRIG_PIN        6
#define ECHO_PIN        5

SonicRanger ranger(TRIG_PIN, ECHO_PIN);

void setup()
{
    Serial.begin(115200);
    ranger.begin();
    delay(300);
    DBLN("setup() complete");
}

void loop()
{
    unsigned long before = Millis();
    uint16_t cm = ranger.getRange();
    unsigned long after = Millis();
    DB("range = ");
    DB(cm);
    DB(" cm, took ");
    DB(after - before);
    DBLN("ms");
    delay(500);
}

