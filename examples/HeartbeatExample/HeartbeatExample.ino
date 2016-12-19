#include <Arduino.h>
#include <ToggleButton.h>
#include <Heartbeat.h>

#define BUT_PIN 2
#define LED_PIN 13

ToggleButton button(BUT_PIN);
Heartbeat heartbeat(LED_PIN);

void setup()
{
    Serial.begin(115200);
    button.begin();
    heartbeat.begin();
    delay(300);
    Serial.println("setup end");
}

void loop()
{
    heartbeat.update();
    button.update();

    heartbeat.setMode(button.on() ? Heartbeat::Quick : Heartbeat::Normal);
}

