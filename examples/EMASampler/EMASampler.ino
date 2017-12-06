#include <EMASampler.h>
#include <Millis.h>
#include <MutilaDebug.h>

EMASampler SlowSampler(A0, 100, 0.02);
EMASampler FastSampler(A0, 100, 0.95);

const uint32_t DebugDelay = 100;
uint32_t LastDb = 0;

void setup()
{
    Serial.begin(115200);
    SlowSampler.begin();
    FastSampler.begin();

    // Show we can handle Millis wrap
    addMillisOffset(0xFFFFF000);

    // Settle down
    delay(300);
    DBLN("setup() complete");
}

void loop()
{
    SlowSampler.update();
    FastSampler.update();

    if (DoEvery(DebugDelay, LastDb)) {
        DB("Millis=0x");
        DB(Millis(), HEX);
        DB(" Slow last=");
        DB(SlowSampler.last());
        DB(" moving average=");
        DB(SlowSampler.average());
        DB("  Fast last=");
        DB(FastSampler.last());
        DB(" moving average=");
        DBLN(FastSampler.average());
    }
}

