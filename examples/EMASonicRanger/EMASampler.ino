#include <EMASonicRanger.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t TrigPin = 2;
const uint8_t EchoPin = 3;

EMASonicRanger Ranger(TrigPin, EchoPin);
uint32_t LastMessage = 0;

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

    if (MillisSince(LastMessage) > 50) {
        LastMessage = Millis();
        DB("Millis=0x");
        DB(Millis(), HEX);
        DB(" range=");
        DBLN(Ranger.getRange());
    }
}

