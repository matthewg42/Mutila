#include <Arduino.h>
#include <MutilaDebug.h>
#include <SonicRanger.h>
#include <Millis.h>

#if defined(ARDUINO_ESP8266_NODEMCU) 
const uint8_t TriggerPin = D3;
const uint8_t EchoPin = D0;
#else
const uint8_t TriggerPin = 3;
const uint8_t EchoPin = 4;
#endif

SonicRanger Ranger(TriggerPin, EchoPin);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show we can handle Millis wrap
    AddMillisOffset(0xFFFFF000);

    // Initialize our ranger
    Ranger.begin();

    Serial.println("setup() end");
}

void loop()
{
    // Get the range, and record time before and after to 
    // work out how long the getRange() call takes
    uint32_t before = Millis();
    uint16_t cm = Ranger.getRange();
    uint32_t after = Millis();

    Serial.print("Millis=0x");
    Serial.print(Millis(), HEX);
    Serial.print(" range = ");
    Serial.print(cm);
    Serial.print(" cm, took ");
    Serial.print(MillisSince(before, after));
    Serial.println("ms");

    delay(50);
}

