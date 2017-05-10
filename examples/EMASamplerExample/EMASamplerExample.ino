#include <EMASampler.h>
#include <MutilaDebug.h>

EMASampler sampler(A0, 50, 0.2);

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
    DB(" last=");
    DB(sampler.last());
    DB(" average=");
    DBLN(sampler.average());
    delay(20);
}

