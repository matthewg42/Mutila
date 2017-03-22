#include <Arduino.h>
#include <MutilaDebug.h>
#include <DebouncedButton.h>
#include <Millis.h>

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
    if (Millis() > next) {
        next = millis() + OUTPUT_MS;
        Serial.print("DebouncedButton: on=");
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

