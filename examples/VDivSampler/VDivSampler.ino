#include <BufferedVDivSampler.h>
#include <EMAVDivSampler.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t VoltPin = A5;
const uint16_t R1KOhms = 20;
const uint16_t R2KOhms = 200;
const float ReferenceVolts = 5.0;
const uint16_t SamplePeriodMs = 50;
const uint16_t BufferedSampleCount = 20;
const float Alpha = 0.1;

// Compare two methods for smoothing VDIV readings.
BufferedVDivSampler SamplerUsingBuffer(VoltPin, R1KOhms, R2KOhms, ReferenceVolts, SamplePeriodMs, BufferedSampleCount);
EMAVDivSampler      SamplerUsingEMA   (VoltPin, R1KOhms, R2KOhms, ReferenceVolts, SamplePeriodMs, Alpha);

// Globals use to rate-limit the output
const uint16_t OutputPeriodMs = 100;
uint32_t LastOutputMs = 0;

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    // Initialize our objects
    SamplerUsingBuffer.begin();
    SamplerUsingEMA.begin();

    // Let analog pin settle after powerup
    delay(300);

    Serial.println("setup() end");
}

void loop()
{
    // Give a timeslice to our samplers so they can read the analog pin
    SamplerUsingBuffer.update();
    SamplerUsingEMA.update();

    if (DoEvery(OutputPeriodMs, LastOutputMs)) {
        Serial.print("0x");
        Serial.print(Millis(), HEX);
        Serial.print(" last volts=");
        Serial.print(SamplerUsingEMA.lastVolts());
        Serial.print(" buffered average=");
        Serial.print(SamplerUsingBuffer.averageVolts());
        Serial.print(" EMA=");
        Serial.println(SamplerUsingEMA.averageVolts());
    }
}

