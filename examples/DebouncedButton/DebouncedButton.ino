#include <Arduino.h>
#include <MutilaDebug.h>
#include <DebouncedButton.h>
#include <Millis.h>

const uint8_t ButtonPin = 6;
const uint16_t OutputMs = 150;
uint32_t LastDb = 0;

DebouncedButton MyButton(ButtonPin);

void setup()
{
    Serial.begin(115200);
    MyButton.begin();
    delay(300);
    addMillisOffset(0xFFFFF000);
    DBLN("setup() complete");
}

void loop()
{
    MyButton.update();
    if (DoEvery(OutputMs, LastDb)) {
        DB("Millis=0x");
        DB(Millis(), HEX);
        DB(" DebouncedButton: on=");
        DB(MyButton.on());
        DB(" pushed=");
        DB(MyButton.pushed());
        DB(" held=");
        DB(MyButton.held());
        DB(" repeat=");
        DB(MyButton.repeat());
        DB(" tapped=");
        DBLN(MyButton.tapped());
    }
}

