#include <Arduino.h>
#include <DigitalInputButton.h>
#include <AnalogInputButton.h>
#include <DualInputButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t DigitalInputButtonPin = 6;
const uint8_t AnalogInputButtonPin = A0;
const uint8_t LedPin = 13;
bool previousValue = false;
uint32_t LastDb = 0;

DigitalInputButton Button1(DigitalInputButtonPin);
AnalogInputButton Button2(AnalogInputButtonPin);
DualInputButton CombinedButtonOr(Button1, Button2); // default is Or mode
DualInputButton CombinedButtonXor(Button1, Button2, DualInputButton::Xor);
DualInputButton CombinedButtonAnd(Button1, Button2, DualInputButton::And);

void setup()
{
    Serial.begin(115200);

    // We don't need to call begin() for Button1 and Button2
    // because CombinedButton.begin() will do it for us.
    CombinedButtonOr.begin();
    CombinedButtonXor.begin(false);
    CombinedButtonAnd.begin(false);

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
        DB(" CombinedButtonOr on=");
        DB(CombinedButtonOr.on());
        DB(" CombinedButtonXor on=");
        DB(CombinedButtonXor.on());
        DB(" CombinedButtonAnd on=");
        DBLN(CombinedButtonAnd.on());
    }
}


