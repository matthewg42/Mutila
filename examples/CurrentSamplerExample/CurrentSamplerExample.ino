#include <EMACurrentSampler.h>
#include <Millis.h>

// Compare two methods for smoothing VDIV readings.

EMACurrentSampler sampler(A0, 20, 5, 0.2, 0, 0.4);

void setup()
{
    Serial.begin(115200);
    sampler.begin();
    // Settle down
    delay(300);
    Serial.println("millis,raw,average");
}

void loop()
{
    sampler.update();
    Serial.print(Millis());
    Serial.print(',');
    Serial.print(sampler.lastAmps());
    Serial.print(',');
    Serial.println(sampler.averageAmps());
    delay(20);
}

