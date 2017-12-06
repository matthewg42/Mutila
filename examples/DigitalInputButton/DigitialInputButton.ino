#include <Arduino.h>
#include <DigitalInputButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t ButtonPin = 6;
const uint8_t LedPin = 13;
uint32_t LastDb = 0;

DigitalInputButton Button(ButtonPin);

void setup()
{
    Serial.begin(115200);
    Button.begin();
    pinMode(LedPin, OUTPUT);
    // Show we can handle Millis wrap
    addMillisOffset(0xFFFFF000);
    // Settle down
    delay(300);
    DBLN("setup() complete");
}

void loop()
{
    bool isOn = Button.on();
    digitalWrite(LedPin, isOn);
    if (DoEvery(200, LastDb)) {
        DB("Millis=0x");
        DB(Millis(), HEX);
        DB(" button value=");
        DBLN(isOn);
    }
}

