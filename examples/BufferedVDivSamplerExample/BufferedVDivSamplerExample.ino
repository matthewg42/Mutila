#include <BufferedVDivSampler.h>

BufferedVDivSampler sampler(A0, 20, 200, 5.0, 50, 10);

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
    Serial.print("lastVolts=");
    Serial.print(sampler.lastVolts());
    Serial.print(" averageVolts=");
    Serial.println(sampler.averageVolts());
    delay(20);
}

