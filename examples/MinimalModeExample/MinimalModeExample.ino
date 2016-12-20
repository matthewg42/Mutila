#include <Arduino.h>
#include "ModeOne.h"

ModeOne mode;

void setup()
{
    Serial.begin(115200);
    // Settle down
    delay(300);
    Serial.println("setup end");
}

void loop()
{
    mode.update();
}

