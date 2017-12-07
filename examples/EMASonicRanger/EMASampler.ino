#include <EMASonicRanger.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t TriggerPin = 3;
const uint8_t EchoPin = 4;

EMASonicRanger Ranger(TriggerPin, EchoPin);
uint32_t LastDb = 0;

void setup()
{
    Serial.begin(115200);
    Ranger.begin();

    // Show we can handle Millis wrap
    addMillisOffset(0xFFFFF000);

    // Settle down
    delay(300);
    Serial.println("setup() complete");
}

void loop()
{
    Ranger.update();

    if (DoEvery(50, LastDb)) {
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" range=");
        Serial.println(Ranger.getRange());
    }
}

