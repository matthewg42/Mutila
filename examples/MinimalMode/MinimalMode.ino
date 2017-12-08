#include <Arduino.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include "ModeOne.h"

ModeOne mode;

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show we can handle Millis wrap
    AddMillisOffset(0xFFFFF000);

    // Initialize and start our mode
    mode.begin();
    mode.start();

    Serial.println("setup() end");
}

void loop()
{
    // Give our mode a time slice
    mode.update();
}

