#include <Arduino.h>
#include <MutilaDebug.h>
#include <DebouncedButton.h>
#include <Heartbeat.h>
#include <Millis.h>

const uint8_t ButPin = 6;
const uint8_t LedPin = 13;
uint32_t LastMessage = 0;

DebouncedButton button(ButPin);
Heartbeat heartbeat(LedPin);

void setup()
{
    Serial.begin(115200);
    button.begin();
    heartbeat.begin();

    // Show that we're working over Millis() wrap around
    addMillisOffset(0xFFFFF000);

    delay(100);
    Serial.println("E:setup");
}

void loop()
{
    heartbeat.update();
    button.update();

    // Show that we're working over Millis() wrap around
    if (DoEvery(100, LastMessage)) {
        Serial.print("Millis=0x");
        Serial.println(Millis(), HEX);
    }

    if (button.tapped()) {
        switch (heartbeat.mode()) {
        case Heartbeat::Normal:
            Serial.println("Quick");
            heartbeat.setMode(Heartbeat::Quick);
            break;
        case Heartbeat::Quick:
            Serial.println("Quicker");
            heartbeat.setMode(Heartbeat::Quicker);
            break;
        case Heartbeat::Quicker:
            Serial.println("Slow");
            heartbeat.setMode(Heartbeat::Slow);
            break;
        case Heartbeat::Slow:
            Serial.println("Slower");
            heartbeat.setMode(Heartbeat::Slower);
            break;
        case Heartbeat::Slower:
            Serial.println("Off");
            heartbeat.setMode(Heartbeat::Off);
            break;
        case Heartbeat::Off:
            Serial.println("On");
            heartbeat.setMode(Heartbeat::On);
            break;
        case Heartbeat::On:
            Serial.println("Custom");
            heartbeat.setCustomMode(450, 50);
            break;
        case Heartbeat::Custom:
            Serial.println("Normal");
            heartbeat.setMode(Heartbeat::Normal);
            break;
        }
    }
}

