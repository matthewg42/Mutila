#include <EMASampler.h>
#include <Millis.h>
#include <MutilaDebug.h>

EMASampler SlowSampler(A7, 100, 0.02);
EMASampler FastSampler(A7, 100, 0.95);

uint32_t LastMessage = 0;

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

    if (MillisSince(LastMessage) > 50) {
        LastMessage = Millis();
        DB("Millis=0x");
        DB(Millis(), HEX);
        DB(" Slow last=");
        DB(SlowSampler.last());
        DB(" average=");
        DB(SlowSampler.average());
        DB("  Fast last=");
        DB(FastSampler.last());
        DB(" average=");
        DBLN(FastSampler.average());
    }
}

