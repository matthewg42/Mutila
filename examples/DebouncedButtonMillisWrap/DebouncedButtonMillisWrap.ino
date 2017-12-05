/*
 * Example to test DebouncedButton handles Millis() wrap OK
 * Press and hold the button until the Millis() wrap, and then
 * release. Value for tapped() should be sane.
 *
 */

#include <Arduino.h>
#include <MutilaDebug.h>
#include <DebouncedButton.h>
#include <Millis.h>

const uint8_t   ButPin =            3;
const uint16_t  OutputPeriodMs =    100;

DebouncedButton Button(ButPin);
uint32_t PreviousOutput = 0;

void setup()
{
    Serial.begin(115200);
    Button.begin();
    addMillisOffset(0xFFFFF000);
    delay(100);
    DBLN("setup() complete");
}

void loop()
{
    Button.update();
    if (MillisSince(PreviousOutput) > OutputPeriodMs) {
        PreviousOutput = Millis();
        DB("Millis=0x");
        DB(PreviousOutput, HEX);
        DB(" on=");
        DB(Button.on());
        DB(" pushed=");
        DB(Button.pushed());
        DB(" held=");
        DB(Button.held());
        DB(" repeat=");
        DB(Button.repeat());
        DB(" tapped=");
        DBLN(Button.tapped());
    }
}

