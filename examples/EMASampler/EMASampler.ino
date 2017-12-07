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
    Serial.println("setup() complete");
}

void loop()
{
    SlowSampler.update();
    FastSampler.update();

    if (DoEvery(DebugDelay, LastDb)) {
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" Slow last=");
        Serial.print(SlowSampler.last());
        Serial.print(" moving average=");
        Serial.print(SlowSampler.average());
        Serial.print("  Fast last=");
        Serial.print(FastSampler.last());
        Serial.print(" moving average=");
        Serial.println(FastSampler.average());
    }
}

