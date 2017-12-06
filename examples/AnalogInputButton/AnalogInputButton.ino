#include <Arduino.h>
#include <AnalogInputButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t ButtonPin = A0;
const uint8_t LedPin = 13;
bool previousValue = false;
uint32_t LastDb = 0;

AnalogInputButton Button(ButtonPin);

// Function prototypes. Not necessary for the IDE, but when building with
// make, we need them if we're to put setup and loop at the top of this
// file.
void setup();
void loop();
void checkButton();

void setup()
{
    Serial.begin(115200);
    Button.begin();
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
    bool newValue = Button.on();
    if (newValue != previousValue || DoEvery(200, LastDb)) {
        DB("Millis=0x");
        DB(Millis(), HEX);
        DB(" analog value=");
        DB(analogRead(ButtonPin));
        DB(" logical button value=");
        DBLN(newValue);
        previousValue = newValue;
        digitalWrite(LedPin, newValue);
    }
}

