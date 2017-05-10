#include <Arduino.h>
#include <DebouncedButton.h>
#include <Heartbeat.h>
#include <MutilaDebug.h>

#define BUT_PIN 7
#define LED_PIN 13

DebouncedButton button(BUT_PIN);
Heartbeat heartbeat(LED_PIN);

void setup()
{
    Serial.begin(115200);
    button.begin();
    heartbeat.begin();
    delay(300);
    DBLN("setup end");
}

void loop()
{
    heartbeat.update();
    button.update();

    if (button.tapped()) {
        switch (heartbeat.mode()) {
        case Heartbeat::Normal:
            heartbeat.setMode(Heartbeat::Quick);
            break;
        case Heartbeat::Quick:
            heartbeat.setMode(Heartbeat::Slow);
            break;
        case Heartbeat::Slow:
            heartbeat.setMode(Heartbeat::Slower);
            break;
        case Heartbeat::Slower:
            heartbeat.setMode(Heartbeat::Off);
            break;
        case Heartbeat::Off:
            heartbeat.setMode(Heartbeat::On);
            break;
        case Heartbeat::On:
            heartbeat.setMode(Heartbeat::Normal);
            break;
        }
    }
}

