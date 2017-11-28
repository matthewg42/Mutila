#include <Arduino.h>
#include <RawButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

#define BUT_PIN 2
#define LED_PIN 13

RawButton MyButton(BUT_PIN);

bool previousValue = false;

void checkButton()
{
    bool newValue = MyButton.on();
    if (newValue != previousValue) {
        DB("Button changed to: ");
        DB(newValue);
        DB(" at Millis()=");
        DBLN(Millis());
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
    DBLN("setup() complete");
}

void loop()
{
    checkButton();
}

