#include <Arduino.h>
#include <DigitalInputButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

#if defined(ARDUINO_ESP8266_NODEMCU) 
const uint8_t ButtonPin = D1;
#else
const uint8_t ButtonPin = 3;
#endif

const uint8_t LedPin = LED_BUILTIN;
const uint16_t OutputPeriodMs = 200;
uint32_t LastOutputMs = 0;

DigitalInputButton Button(ButtonPin);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    // Initialize button object and LED pin
    Button.begin();
    pinMode(LedPin, OUTPUT);

    Serial.println("setup() end");
}

void loop()
{
    bool isOn = Button.on();
    digitalWrite(LedPin, isOn);
    if (DoEvery(OutputPeriodMs, LastOutputMs)) {
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" button value=");
        Serial.println(isOn);
    }
}

