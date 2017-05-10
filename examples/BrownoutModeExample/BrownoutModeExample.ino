#include <Arduino.h>
#include <EMAVDivSampler.h>
#include <MutilaDebug.h>
#include "MyBrownoutMode.h"

EMAVDivSampler vIn(A0, 10, 100, 5, 5, 0.5);
MyBrownoutMode mode(vIn, 10, 15);

void setup()
{
    Serial.begin(115200);
    mode.begin();
    mode.start();
    DBLN("setup() complete");
}

void loop()
{
    mode.update();
}

