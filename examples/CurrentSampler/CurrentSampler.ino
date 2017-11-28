#include <EMACurrentSampler.h>
#include <Millis.h>
#include <MutilaDebug.h>

// Compare two methods for smoothing VDIV readings.

EMACurrentSampler sampler(A0, 20, 5, 0.2, 0, 0.4);

void setup()
{
    Serial.begin(115200);
    sampler.begin();
    // Settle down
    delay(300);
    DBLN("millis,raw,average");
}

void loop()
{
    sampler.update();
    DB(Millis());
    DB(',');
    DB(sampler.lastAmps());
    DB(',');
    DBLN(sampler.averageAmps());
    delay(20);
}

