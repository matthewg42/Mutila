#include <Arduino.h>
#include <DigitalButton.h>
#include <AnalogButton.h>
#include <DualInputButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t DigitalButtonPin = 6;
const uint8_t AnalogButtonPin = A0;
const uint8_t LedPin = 13;
bool previousValue = false;
uint32_t LastDb = 0;

DigitalButton Button1(DigitalButtonPin);
AnalogButton Button2(AnalogButtonPin);
DualInputButton CombinedButton(Button1, Button2);

void setup()
{
    Serial.begin(115200);

    // We don't need to call begin() for Button1 and Button2
    // because CombinedButton.begin() will do it for us.
    CombinedButton.begin();

    pinMode(LedPin, OUTPUT);

    // Show we can handle Millis wrap
    addMillisOffset(0xFFFFF000);

    // Settle down (analog inputs can be a bit weird for a short
    // time after power-up)
    delay(300);

    DBLN("setup() complete");
}

void loop()
{
    if (DoEvery(200, LastDb)) {
        DB("Millis=0x");
        DB(Millis(), HEX);
        DB(" Button1 on=");
        DB(Button1.on());
        DB(" Button2 on=");
        DB(Button2.on());
        DB(" CombinedButton on=");
        DBLN(CombinedButton.on());
    }
}


