#include <Arduino.h>
#include <AnalogInputButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

// Turn on Serial.print output.
#define DEBUG true

const uint8_t ButtonPin = A0;
const uint8_t LedPin = LED_BUILTIN;
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
    Serial.println("setup() complete");
}

void loop()
{
    checkButton();
}

void checkButton()
{
    bool newValue = Button.on();
    if (newValue != previousValue || DoEvery(200, LastDb)) {
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" analog value=");
        Serial.print(analogRead(ButtonPin));
        Serial.print(" logical button value=");
        Serial.println(newValue);
        previousValue = newValue;
        digitalWrite(LedPin, newValue);
    }
}

