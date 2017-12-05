#include <Arduino.h>
#include <DebouncedAnalogButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

DebouncedAnalogButton Button(A0);

uint32_t LastDb = 0;

void setup()
{
    Serial.begin(115200);
    Button.begin();
    addMillisOffset(0xFFFFF000);
    DBLN("setup() complete");
}

void loop() 
{
    Button.update();
    if (DoEvery(100, LastDb)) {
        DB("Millis=0x");
        DB(Millis(), HEX);
        DB(" analog value=");
        DB(analogRead(A0));
        DB(" Button on=");
        DB(Button.on());
        DB(" tapped=");
        DB(Button.tapped());
        DB(" repeat=");
        DB(Button.repeat());
        DB(" held=");
        DBLN(Button.held());
    }
}

