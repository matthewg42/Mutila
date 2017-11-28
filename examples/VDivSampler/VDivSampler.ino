#include <BufferedVDivSampler.h>
#include <EMAVDivSampler.h>
#include <Millis.h>
#include <MutilaDebug.h>

// Compare two methods for smoothing VDIV readings.

BufferedVDivSampler bufSampler(A0, 20, 200, 5.0, 0, 10);
EMAVDivSampler emaSampler(A0, 20, 200, 5.0, 0, 0.4);

void setup()
{
    Serial.begin(115200);
    bufSampler.begin();
    emaSampler.begin();
    // Settle down
    delay(300);
    DBLN("millis,raw,buffer,ema");
}

void loop()
{
    bufSampler.update();
    emaSampler.update();
    DB(Millis());
    DB(',');
    DB(emaSampler.lastVolts());
    DB(',');
    DB(bufSampler.averageVolts());
    DB(',');
    DBLN(emaSampler.averageVolts());
    delay(20);
}

