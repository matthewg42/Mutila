#include <Arduino.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include "ModeOne.h"

ModeOne mode;

void setup()
{
    Serial.begin(115200);
    // Show we can handle Millis wrap
    //addMillisOffset(0xFFFFF000);
    mode.begin();
    mode.start();
    DBLN("setup() complete");
}

void loop()
{
    mode.update();
}

