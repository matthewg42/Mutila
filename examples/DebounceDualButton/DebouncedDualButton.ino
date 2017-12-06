#include <Arduino.h>
#include <MutilaDebug.h>
#include <DigitalButton.h>
#include <AnalogButton.h>
#include <DebouncedDualButton.h>
#include <Millis.h>

const uint8_t DigitalButtonPin = 6;
const uint8_t AnalogButtonPin = A0;
const uint16_t OutputMs = 150;
uint32_t LastDb = 0;

DigitalButton Button1(DigitalButtonPin);
AnalogButton Button2(AnalogButtonPin);
DebouncedDualButton CombinedButton(Button1, Button2);

void setup()
{
    Serial.begin(115200);
    CombinedButton.begin();
    delay(300);
    addMillisOffset(0xFFFFF000);
    DBLN("setup() complete");
}

void loop()
{
    CombinedButton.update();
    if (DoEvery(OutputMs, LastDb)) {
        DB("Millis=0x");
        DB(Millis(), HEX);
        DB(" CombinedButton on=");
        DB(CombinedButton.on());
        DB(" pushed=");
        DB(CombinedButton.pushed());
        DB(" held=");
        DB(CombinedButton.held());
        DB(" repeat=");
        DB(CombinedButton.repeat());
        DB(" tapped=");
        DBLN(CombinedButton.tapped());
    }
}

