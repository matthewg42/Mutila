#include <EMACurrentSampler.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t CurrentSamplePin = A0;
const float VSupply = 20.0;
const float VRef = 5.0;
const float IOffset = 0.2;
const uint16_t SamplePeriodMs = 10;
const float Alpha = 0.5;
const uint16_t OutputPeriodMs = 100;

EMACurrentSampler Sampler(CurrentSamplePin, VSupply, VRef, IOffset, SamplePeriodMs, Alpha);
uint32_t LastOutputMs = 0;

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    // Initialize sampler
    Sampler.begin();

    // let analog pin settle after powerup
    delay(300);

    Serial.println("setup() end");
}

void loop()
{
    Sampler.update();
    if (DoEvery(OutputPeriodMs, LastOutputMs)) {
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" last amps=");
        Serial.print(Sampler.lastAmps());
        Serial.print(" average=");
        Serial.println(Sampler.averageAmps());
    }
}

