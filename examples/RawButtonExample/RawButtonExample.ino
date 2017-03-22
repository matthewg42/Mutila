#include <Arduino.h>
#include <RawButton.h>
#include <Millis.h>

#define BUT_PIN 2
#define LED_PIN 13

RawButton MyButton(BUT_PIN);

bool previousValue = false;

void checkButton()
{
    bool newValue = MyButton.on();
    if (newValue != previousValue) {
        Serial.print("Button changed to: ");
        Serial.print(newValue);
        Serial.print(" at millis()=");
        Serial.println(millis());
        previousValue = newValue;
        digitalWrite(LED_PIN, newValue);
    }
}

void setup()
{
    Serial.begin(115200);
    MyButton.begin();
    pinMode(LED_PIN, OUTPUT);

    // Settle down
    delay(300);
    checkButton();
    Serial.println("setup end");
}

void loop()
{
    checkButton();
}

