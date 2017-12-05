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

#define BUT_PIN 3
#define OUTPUT_MS 100

DebouncedButton MyButton(BUT_PIN);
unsigned long prev = 0;

void setup()
{
    Serial.begin(115200);
    MyButton.begin();
    addMillisOffset(0xFFFFF000);
    delay(100);
    DBLN("setup() complete");
}

void loop()
{
    MyButton.update();
    if (MillisSince(prev) > OUTPUT_MS) {
        prev = Millis();
        DB("Millis=0x");
        DB(prev, HEX);
        DB(" on=");
        DB(MyButton.on());
        DB(" pushed=");
        DB(MyButton.pushed());
        DB(" held=");
        DB(MyButton.held());
        DB(" repeat=");
        DB(MyButton.repeat());
        DB(" tapped=");
        DBLN(MyButton.tapped());
    }
}

