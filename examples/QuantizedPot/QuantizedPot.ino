#include <Arduino.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include <QuantizedPot.h>

const uint8_t AnalogPin = A5;
const uint16_t OutputPeriodMs = 100;

uint32_t LastOutputMs = 0;
QuantizedPot Pot(AnalogPin, 4);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show we can handle Millis wrap
    AddMillisOffset(0xFFFFF000);

    // Add some ranges for the various values
    Pot.addRange(0, 100);
    Pot.addRange(100, 400);
    Pot.addRange(400, 450);
    Pot.addRange(450, 1000);

    // Note: the analog pin can value values up to 1023, so there is a part of
    // the range that is missing - when the analog pin returns this value, the
    // Pot object's value will be -1 to indicate a value which is not in one 
    // of the specified ranges.

    // Initialize objects
    Pot.begin();

    // Allow analog pin to settle after powerup
    delay(300);
    Serial.println("setup() end");
}

void loop()
{
    Pot.update();

    if (DoEvery(OutputPeriodMs, LastOutputMs)) {
        Serial.print("Millis=0x");
        Serial.print(Millis());
        Serial.print(" analog value=");
        Serial.print(analogRead(AnalogPin));
        Serial.print(" Pot.value()=");
        Serial.println(Pot.value());
    }
}

