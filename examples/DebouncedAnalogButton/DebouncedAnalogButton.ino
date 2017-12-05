#include <Arduino.h>
#include <DebouncedAnalogButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

DebouncedAnalogButton b1(A0);
DebouncedAnalogButton b2(A1);

uint32_t LastDb = 0;

void setup()
{
    Serial.begin(115200);
    b1.begin();
    b2.begin();
    addMillisOffset(0xFFFFF000);
    DBLN("setup() complete");
}

void loop() 
{
    b1.update();
    b2.update();
    if (DoEvery(100, LastDb)) {
        DB("Millis=0x");
        DB(Millis(), HEX);
        DB(" b1 on=");
        DB(b1.on());
        DB(" tapped=");
        DB(b1.tapped());
        DB(" repeat=");
        DB(b1.repeat());
        DB(" held=");
        DB(b1.held());
        DB("  b2 on=");
        DB(b2.on());
        DB(" tapped=");
        DB(b2.tapped());
        DB(" tapped=");
        DB(b2.repeat());
        DB(" held=");
        DBLN(b2.held());
    }
}

