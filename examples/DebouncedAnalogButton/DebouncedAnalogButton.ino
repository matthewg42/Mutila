#include <Arduino.h>
#include <DebouncedAnalogButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t ButtonPin = A5;
DebouncedAnalogButton Button(ButtonPin);

const uint16_t OutputPeriodMs = 100;
uint32_t LastOutputMs = 0;

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() end");

    // Show we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    // Initialize button object
    Button.begin();

    Serial.println("setup() end");
}

void loop() 
{
    Button.update();
    if (DoEvery(OutputPeriodMs, LastOutputMs)) {
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" analog value=");
        Serial.print(analogRead(ButtonPin));
        Serial.print(" logical button value=");
        Serial.print(Button.on());
        Serial.print(" tapped=");
        Serial.print(Button.tapped());
        Serial.print(" repeat=");
        Serial.print(Button.repeat());
        Serial.print(" held=");
        Serial.println(Button.held());
    }
}

