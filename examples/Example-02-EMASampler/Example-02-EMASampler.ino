#include <EMASampler.h>

EMASampler sampler(A0, 50, 0.2);

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
    Serial.print(" last=");
    Serial.print(sampler.last());
    Serial.print(" average=");
    Serial.println(sampler.average());
    delay(20);
}

