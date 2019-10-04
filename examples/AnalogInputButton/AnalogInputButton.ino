#include <Arduino.h>
#include <AnalogInputButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t ButtonPin = A0;
const uint8_t LedPin = LED_BUILTIN;
const uint16_t OutputPeriodMs = 200;
uint32_t LastOutputMs = 0;
bool previousValue = false;

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
    Serial.println("\n\nsetup() start");

    // Show we can handle Millis wrap
    AddMillisOffset(0xFFFFF000);

    // Initalize the button and LED pin
    Button.begin();
    pinMode(LedPin, OUTPUT);

    // Let analog pins settle after powerup
    delay(300);

    Serial.println("setup() end");
}

void loop()
{
    checkButton();
}

void checkButton()
{
    bool newValue = Button.on();
    if (newValue != previousValue || DoEvery(OutputPeriodMs, LastOutputMs)) {
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
