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
    DBLN("setup() complete");
}

void loop()
{
    heartbeat.update();
    button.update();

    if (button.tapped()) {
        switch (heartbeat.mode()) {
        case Heartbeat::Normal:
            DBLN("Quick");
            heartbeat.setMode(Heartbeat::Quick);
            break;
        case Heartbeat::Quick:
            DBLN("Quicker");
            heartbeat.setMode(Heartbeat::Quicker);
            break;
        case Heartbeat::Quicker:
            DBLN("Slow");
            heartbeat.setMode(Heartbeat::Slow);
            break;
        case Heartbeat::Slow:
            DBLN("Slower");
            heartbeat.setMode(Heartbeat::Slower);
            break;
        case Heartbeat::Slower:
            DBLN("Off");
            heartbeat.setMode(Heartbeat::Off);
            break;
        case Heartbeat::Off:
            DBLN("On");
            heartbeat.setMode(Heartbeat::On);
            break;
        case Heartbeat::On:
            DBLN("Custom");
            heartbeat.setCustomMode(450, 50);
            break;
        case Heartbeat::Custom:
            DBLN("Normal");
            heartbeat.setMode(Heartbeat::Normal);
            break;
        }
    }
}

