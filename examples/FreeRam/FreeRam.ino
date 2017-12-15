#include <Arduino.h>
#include <MutilaDebug.h>
#include <FreeRam.h>
#include <Millis.h>

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show that we're working over Millis() wrap around
    AddMillisOffset(0xFFFFF000);

    Serial.println("setup() end");
}

void loop()
{
    // Let's leak some memory!
    uint32_t* i = new uint32_t;

    Serial.print("Millis=0x");
    Serial.print(Millis(), HEX);
    Serial.print(" FreeRam=");
    Serial.print(FreeRam());
    Serial.print(" Allocated address=0x");
    Serial.println((uint32_t)i, HEX);
}

