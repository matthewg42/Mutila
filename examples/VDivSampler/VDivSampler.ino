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
    // Show we can handle Millis wrap
    addMillisOffset(0xFFFFF000);
    // Settle down
    delay(300);
    Serial.println("millis,raw,buffer,ema");
}

void loop()
{
    bufSampler.update();
    emaSampler.update();
    Serial.print("0x");
    Serial.print(Millis(), HEX);
    Serial.print(',');
    Serial.print(emaSampler.lastVolts());
    Serial.print(',');
    Serial.print(bufSampler.averageVolts());
    Serial.print(',');
    Serial.println(emaSampler.averageVolts());
    delay(20);
}

