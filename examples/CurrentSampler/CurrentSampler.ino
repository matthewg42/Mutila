#include <EMACurrentSampler.h>
#include <Millis.h>
#include <MutilaDebug.h>

EMACurrentSampler sampler(A0, 20, 5, 0.2, 0, 0.4);
uint32_t LastDb = 0;

void setup()
{
    Serial.begin(115200);
    sampler.begin();
    // show code works over Millis wrap
    addMillisOffset(0xFFFFF000);
    // Settle down
    delay(300);
    DBLN("millis,raw,average");
}

void loop()
{
    sampler.update();
    if (DoEvery(100, LastDb)) {
        DB("0x");
        DB(Millis(), HEX);
        DB(',');
        DB(sampler.lastAmps());
        DB(',');
        DBLN(sampler.averageAmps());
    }
}

