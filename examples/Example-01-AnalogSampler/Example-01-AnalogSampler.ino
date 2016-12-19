#include <AnalogSampler.h>

AnalogSampler sampler(A0, 5, 500);

void setup()
{
    Serial.begin(115200);
    sampler.begin();
    // Settle down
    delay(300);
    Serial.println("setup end");
}

void loop()
{
    sampler.update();
    Serial.print("count=");
    Serial.print(sampler.count());
    Serial.print(" last=");
    Serial.print(sampler.last());
    Serial.print(" minimum=");
    Serial.print(sampler.minimum());
    Serial.print(" maximum=");
    Serial.print(sampler.maximum());
    Serial.print(" average=");
    Serial.println(sampler.average());
}

