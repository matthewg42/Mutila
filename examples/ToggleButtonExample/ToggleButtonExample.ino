#include <Arduino.h>
#include <ToggleButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

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
    DBLN("setup() complete");
}

void loop()
{
    MyButton.update();
    if (Millis() > next) {
        next = Millis() + OUTPUT_MS;
        bool o = MyButton.on();
        DB("ToggleButton.on()=");
        DBLN(o);
        digitalWrite(LED_PIN, o);
    }
}

