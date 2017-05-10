#include <BufferedSampler.h>
#include <MutilaDebug.h>

BufferedSampler sampler(A0, 50, 10);

void setup()
{
    Serial.begin(115200);
    sampler.begin();
    // Settle down
    delay(300);
    DBLN("setup end");
}

void loop()
{
    sampler.update();
    DB("count=");
    DB(sampler.count());
    DB(" last=");
    DB(sampler.last());
    DB(" minimum=");
    DB(sampler.minimum());
    DB(" maximum=");
    DB(sampler.maximum());
    DB(" average=");
    DBLN(sampler.average());
    delay(20);
}

