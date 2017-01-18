#include <Arduino.h>
#include <DebouncedAnalogButton.h>

DebouncedAnalogButton b1(A6);
DebouncedAnalogButton b2(A7);

unsigned long last = 0;

void setup()
{
    Serial.begin(115200);
    b1.begin();
    b2.begin();
}

void loop() 
{
    b1.update();
    b2.update();
    if (millis() > last + 50) {
        Serial.print("b1 on=");
        Serial.print(b1.on());
        Serial.print(" tapped=");
        Serial.print(b1.tapped());
        Serial.print(" held=");
        Serial.print(b1.held());
        Serial.print("  b2 on=");
        Serial.print(b2.on());
        Serial.print(" tapped=");
        Serial.print(b2.tapped());
        Serial.print(" held=");
        Serial.println(b2.held());
    }
}
