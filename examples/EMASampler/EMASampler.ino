#include <EMASampler.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t SamplerPin = A0;
const uint16_t SamplePeriodMs = 50;

// We'll create two samplers with a different alpha value
// which take input from the same pin so we can compare them
EMASampler SlowSampler(SamplerPin, SamplePeriodMs, 0.02);
EMASampler FastSampler(SamplerPin, SamplePeriodMs, 0.95);

// How often to print output
const uint32_t OutputPeriodMs = 100;
// Timer to keep track of when we last printed output
uint32_t LastOutputMs = 0;

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");
    
    // Show we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    // Initialize the samplers
    SlowSampler.begin();
    FastSampler.begin();

    // Let analog inputs settle after powerup
    delay(300);

    Serial.println("setup() end");
}

void loop()
{
    // Give out samplers a timeslice to do their sampling when
    // it is time to do so.
    SlowSampler.update();
    FastSampler.update();

    if (DoEvery(OutputPeriodMs, LastOutputMs)) {
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

