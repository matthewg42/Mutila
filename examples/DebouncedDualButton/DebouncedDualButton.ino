#include <Arduino.h>
#include <MutilaDebug.h>
#include <DigitalInputButton.h>
#include <AnalogInputButton.h>
#include <DebouncedDualButton.h>
#include <Millis.h>

const uint8_t DigitalInputButtonPin = 6;
const uint8_t AnalogInputButtonPin = A0;
const uint16_t OutputMs = 150;
uint32_t LastDb = 0;

DigitalInputButton Button1(DigitalInputButtonPin);
AnalogInputButton Button2(AnalogInputButtonPin);
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

