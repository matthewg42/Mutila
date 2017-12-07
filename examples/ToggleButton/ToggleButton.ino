#include <Arduino.h>
#include <ToggleButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t ButtonPin = 6;
const uint8_t LedPin = 13;
const uint8_t OutputMs = 50;
uint32_t LastDb = 0;

ToggleButton MyButton(ButtonPin);

void setup()
{
    Serial.begin(115200);
    MyButton.begin();
    pinMode(LedPin, OUTPUT);
    // Show that code works over Millis wrap
    addMillisOffset(0xFFFFF000);
    Serial.println("setup() complete");
}

void loop()
{
    MyButton.update();
    if (DoEvery(OutputMs, LastDb)) {
        bool o = MyButton.on();
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" ToggleButton.on()=");
        Serial.println(o);
        digitalWrite(LedPin, o);
    }
}

