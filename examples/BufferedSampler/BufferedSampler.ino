#include <BufferedSampler.h>
#include <Millis.h>
#include <MutilaDebug.h>

BufferedSampler Sampler(A0, 100, 10);

void setup()
{
    Serial.begin(115200);
    Sampler.begin();

    // Show that things work over Millis wrap
    addMillisOffset(0xFFFFF000);

    // Settle down
    delay(300);
    Serial.println("setup() complete");
}

void loop()
{
    Sampler.update();
    Serial.print("Millis=0x");
    Serial.print(Millis(), HEX);
    Serial.print(" count=");
    Serial.print(Sampler.count());
    Serial.print(" last=");
    Serial.print(Sampler.last());
    Serial.print(" minimum=");
    Serial.print(Sampler.minimum());
    Serial.print(" maximum=");
    Serial.print(Sampler.maximum());
    Serial.print(" average=");
    Serial.println(Sampler.average());
    delay(30);
}

