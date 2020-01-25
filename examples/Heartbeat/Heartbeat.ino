#include <Arduino.h>
#include <MutilaDebug.h>
#include <DebouncedButton.h>
#include <Heartbeat.h>
#include <Millis.h>
#include "TestBoardPins.h"

#if defined(ARDUINO_ESP8266_NODEMCU) 
// The builtin LED in the NODEMCU has inverted logic
Heartbeat heartbeat(LedPin, true); 
#else
Heartbeat heartbeat(LedPin); 
#endif

DebouncedButton button(Button1Pin);

// Function prototypes are useful when building with make, as they
// enable us to order the functions in the file in the order we choose
// instead of defining them before they are called.  This isn't needed
// if building with the IDE, or you don't care about the order of the
// functions in the file.
void setup();
void loop();
void printWithMillis(const char* str);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show that we're working over Millis() wrap around
    AddMillisOffset(0xFFFFF000);

    // Initialize our objects
    button.begin();
    heartbeat.begin();

    Serial.println("Press primary button to modify heartbeat pattern");
    Serial.println("setup() end");
}

void loop()
{
    // Give a timeslice to our objects
    heartbeat.update();
    button.update();

    // When tr
    if (button.pushed()) {
        switch (heartbeat.mode()) {
        case Heartbeat::Normal:
            printWithMillis("Quick");
            heartbeat.setMode(Heartbeat::Quick);
            break;
        case Heartbeat::Quick:
            printWithMillis("Quicker");
            heartbeat.setMode(Heartbeat::Quicker);
            break;
        case Heartbeat::Quicker:
            printWithMillis("Slow");
            heartbeat.setMode(Heartbeat::Slow);
            break;
        case Heartbeat::Slow:
            printWithMillis("Slower");
            heartbeat.setMode(Heartbeat::Slower);
            break;
        case Heartbeat::Slower:
            printWithMillis("Off");
            heartbeat.setMode(Heartbeat::Off);
            break;
        case Heartbeat::Off:
            printWithMillis("On");
            heartbeat.setMode(Heartbeat::On);
            break;
        case Heartbeat::On:
            printWithMillis("Custom");
            heartbeat.setCustomMode(450, 50);
            break;
        case Heartbeat::Custom:
            printWithMillis("Normal");
            heartbeat.setMode(Heartbeat::Normal);
            break;
        }
    }
}

void printWithMillis(const char* str)
{
    Serial.print("Millis=0x");
    Serial.print(Millis(), HEX);
    Serial.print(' ');
    Serial.println(str);
}

