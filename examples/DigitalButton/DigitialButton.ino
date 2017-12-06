#include <Arduino.h>
#include <DigitalButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t ButtonPin = 6;
const uint8_t LedPin = 13;
bool previousValue = false;

DigitalButton MyButton(ButtonPin);

// Function prototypes. Not necessary for the IDE, but when building with
// make, we need them if we're to put setup and loop at the top of this
// file.
void setup();
void loop();
void checkButton();

void setup()
{
    Serial.begin(115200);
    MyButton.begin();
    pinMode(LedPin, OUTPUT);
    // Show we can handle Millis wrap
    addMillisOffset(0xFFFFF000);
    // Settle down
    delay(300);
    checkButton();
    DBLN("setup() complete");
}

void loop()
{
    checkButton();
}

void checkButton()
{
    bool newValue = MyButton.on();
    if (newValue != previousValue) {
        DB("Millis=0x");
        DB(Millis(), HEX);
        DB(" button changed to: ");
        DBLN(newValue);
        previousValue = newValue;
        digitalWrite(LedPin, newValue);
    }
}

