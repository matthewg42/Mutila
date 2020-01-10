#include <Arduino.h>
#include <MutilaDebug.h>
#include <DebouncedButton.h>
#include <Millis.h>

#if defined(ARDUINO_ESP8266_NODEMCU) 
const uint8_t ButtonPin = D1;
#else
const uint8_t ButtonPin = 3;
#endif

const uint16_t OutputPeriodMs = 150;
uint32_t LastOutputMs = 0;

DebouncedButton MyButton(ButtonPin);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    // Initialize button object
    MyButton.begin();

    Serial.println("setup() end");
}

void loop()
{
    MyButton.update();
    if (DoEvery(OutputPeriodMs, LastOutputMs)) {
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" DebouncedButton: on=");
        Serial.print(MyButton.on());
        Serial.print(" pushed=");
        Serial.print(MyButton.pushed());
        Serial.print(" held=");
        Serial.print(MyButton.held());
        Serial.print(" repeat=");
        Serial.print(MyButton.repeat());
        Serial.print(" tapped=");
        Serial.println(MyButton.tapped());
    }
}

