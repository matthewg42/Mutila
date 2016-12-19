#include <Arduino.h>
#include "ToggleButton.h"

#define BUT_PIN 2
#define LED_PIN 13
#define OUTPUT_MS 50

ToggleButton MyButton(BUT_PIN);
unsigned long next = OUTPUT_MS;

void setup()
{
    Serial.begin(115200);
    MyButton.begin();
    pinMode(LED_PIN, OUTPUT);
    delay(300);
    Serial.println("setup end");
}

void loop()
{
    MyButton.update();
    if (millis() > next) {
        next = millis() + OUTPUT_MS;
        bool o = MyButton.on();
        Serial.print("ToggleButton.on()=");
        Serial.println(o);
        digitalWrite(LED_PIN, o);
    }
}

