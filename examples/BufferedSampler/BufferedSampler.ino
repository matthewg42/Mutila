#include <BufferedSampler.h>
#include <Millis.h>
#include <MutilaDebug.h>

BufferedSampler sampler(A7, 100, 10);

void setup()
{
    Serial.begin(115200);
    sampler.begin();

    // Show that things work over Millis wrap
    addMillisOffset(0xFFFFF000);

    // Settle down
    delay(300);
    DBLN("setup() complete");
}

void loop()
{
    sampler.update();
    DB("Millis=0x");
    DB(Millis(), HEX);
    DB(" count=");
    DB(sampler.count());
    DB(" last=");
    DB(sampler.last());
    DB(" minimum=");
    DB(sampler.minimum());
    DB(" maximum=");
    DB(sampler.maximum());
    DB(" average=");
    DBLN(sampler.average());
    delay(30);
}

