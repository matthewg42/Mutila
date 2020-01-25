#include <Arduino.h>
#include <Millis.h>
#include <EMAVDivSampler.h>
#include <MutilaDebug.h>
#include "MyBrownoutMode.h"
#include "TestBoardPins.h"

const uint16_t R1KOhm = 10;
const uint16_t R2KOhm = 100;
const float VRef = 5.0;
const millis_t SamplePeriodMs = 5;
const float Alpha = 0.5;

EMAVDivSampler vIn(VoltagePin, R1KOhm, R2KOhm, VRef, SamplePeriodMs, Alpha);
MyBrownoutMode mode(vIn, 10, 15);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show that we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    mode.begin();
    mode.start();

    Serial.println("setup() end");
}

void loop()
{
    mode.update();
}

