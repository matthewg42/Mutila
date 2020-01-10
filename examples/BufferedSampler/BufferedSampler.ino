#include <BufferedSampler.h>
#include <Millis.h>
#include <MutilaDebug.h>

BufferedSampler Sampler(A5, 100, 10);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show that we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    // Initialize our sampler
    Sampler.begin();

    // Wait for analog pin to settle after powerup
    delay(300);

    Serial.println("setup() end");
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

