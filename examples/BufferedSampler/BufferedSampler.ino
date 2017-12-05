#include <BufferedSampler.h>
#include <Millis.h>
#include <MutilaDebug.h>

BufferedSampler Sampler(A7, 100, 10);

void setup()
{
    Serial.begin(115200);
    Sampler.begin();

    // Show that things work over Millis wrap
    addMillisOffset(0xFFFFF000);

    // Settle down
    delay(300);
    DBLN("setup() complete");
}

void loop()
{
    Sampler.update();
    DB("Millis=0x");
    DB(Millis(), HEX);
    DB(" count=");
    DB(Sampler.count());
    DB(" last=");
    DB(Sampler.last());
    DB(" minimum=");
    DB(Sampler.minimum());
    DB(" maximum=");
    DB(Sampler.maximum());
    DB(" average=");
    DBLN(Sampler.average());
    delay(30);
}

