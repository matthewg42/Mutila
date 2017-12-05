#include <Arduino.h>
#include <ToggleButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t ButtonPin = 6;
const uint8_t LedPin = 13;
const uint8_t OutputMs = 50;

ToggleButton MyButton(ButtonPin);
uint32_t LastDb = 0;

void setup()
{
    Serial.begin(115200);
    MyButton.begin();
    pinMode(LedPin, OUTPUT);
    // Show that code works over Millis wrap
    addMillisOffset(0xFFFFF000);
    DBLN("setup() complete");
}

void loop()
{
    MyButton.update();
    if (DoEvery(OutputMs, LastDb)) {
        bool o = MyButton.on();
        DB("Millis=0x");
        DB(Millis(), HEX);
        DB(" ToggleButton.on()=");
        DBLN(o);
        digitalWrite(LedPin, o);
    }
}

