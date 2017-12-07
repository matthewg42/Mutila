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
    Serial.println("millis,raw,average");
}

void loop()
{
    sampler.update();
    if (DoEvery(100, LastDb)) {
        Serial.print("0x");
        Serial.print(Millis(), HEX);
        Serial.print(',');
        Serial.print(sampler.lastAmps());
        Serial.print(',');
        Serial.println(sampler.averageAmps());
    }
}

