#include <Arduino.h>
#include <MutilaDebug.h>
#include <DigitalInputButton.h>
#include <AnalogInputButton.h>
#include <DebouncedDualButton.h>
#include <Millis.h>

#if defined(ARDUINO_ESP8266_NODEMCU) 
const uint8_t DigitalInputButtonPin = D1;
#else
const uint8_t DigitalInputButtonPin = 9;
#endif

const uint8_t AnalogInputButtonPin = A5;
const uint16_t OutputPeriodMs = 150;
uint32_t LastOutputMs = 0;

DigitalInputButton Button1(DigitalInputButtonPin);
AnalogInputButton Button2(AnalogInputButtonPin);
DebouncedDualButton CombinedButton(Button1, Button2);

void setup()
{
    Serial.begin(115200);
    Serial.println("setup() start");

    // Show we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    // Initialize button object
    CombinedButton.begin();

    // Allow analog pin to settle after poweron
    delay(300);

    Serial.println("setup() end");
}

void loop()
{
    CombinedButton.update();
    if (DoEvery(OutputPeriodMs, LastOutputMs)) {
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" CombinedButton on=");
        Serial.print(CombinedButton.on());
        Serial.print(" pushed=");
        Serial.print(CombinedButton.pushed());
        Serial.print(" held=");
        Serial.print(CombinedButton.held());
        Serial.print(" repeat=");
        Serial.print(CombinedButton.repeat());
        Serial.print(" tapped=");
        Serial.println(CombinedButton.tapped());
    }
}

