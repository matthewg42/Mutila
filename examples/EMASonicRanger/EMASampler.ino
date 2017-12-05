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
    DBLN("setup() complete");
}

void loop()
{
    Ranger.update();

    if (MillisSince(LastDb) > 50) {
        LastDb = Millis();
        DB("Millis=0x");
        DB(Millis(), HEX);
        DB(" range=");
        DBLN(Ranger.getRange());
    }
}

