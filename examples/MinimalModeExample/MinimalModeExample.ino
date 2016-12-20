#include <Arduino.h>
#include "ModeOne.h"

ModeOne mode;

void setup()
{
    Serial.begin(115200);
    mode.begin();
    mode.start();
    Serial.println("setup end");
}

void loop()
{
    mode.update();
}

