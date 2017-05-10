#include <Arduino.h>
#include <MutilaDebug.h>
#include "ModeOne.h"

ModeOne mode;

void setup()
{
    Serial.begin(115200);
    mode.begin();
    mode.start();
    DBLN("setup end");
}

void loop()
{
    mode.update();
}

