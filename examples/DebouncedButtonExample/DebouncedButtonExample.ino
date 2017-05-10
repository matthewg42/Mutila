#include <Arduino.h>
#include <MutilaDebug.h>
#include <DebouncedButton.h>
#include <Millis.h>

#define BUT_PIN 2
#define OUTPUT_MS 50

DebouncedButton MyButton(BUT_PIN);
unsigned long next = OUTPUT_MS;

void setup()
{
    Serial.begin(115200);
    MyButton.begin();
    delay(300);
    DBLN("setup end");
}

void loop()
{
    MyButton.update();
    if (Millis() > next) {
        next = Millis() + OUTPUT_MS;
        DB("DebouncedButton: on=");
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

