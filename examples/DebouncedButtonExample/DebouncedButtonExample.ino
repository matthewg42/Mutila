#include <Arduino.h>
#include "DebouncedButton.h"

#define BUT_PIN 2
#define OUTPUT_MS 50

DebouncedButton MyButton(BUT_PIN);
unsigned long next = OUTPUT_MS;

void setup()
{
    Serial.begin(115200);
    MyButton.begin();

    delay(300);
    Serial.println("setup end");
}

void loop()
{
    MyButton.update();
    if (millis() > next) {
        next = millis() + OUTPUT_MS;
        Serial.print("DebouncedButton: pushed=");
        Serial.print(MyButton.pushed());
        Serial.print(" tapped=");
        Serial.print(MyButton.tapped());
        Serial.print(" held=");
        Serial.print(MyButton.held());
        Serial.print(" repeat=");
        Serial.println(MyButton.repeat());
    }
}

