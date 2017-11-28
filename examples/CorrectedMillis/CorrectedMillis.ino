#include <Arduino.h>
#include <Millis.h>
#include <MutilaDebug.h>

void setup()
{
    Serial.begin(115200);
    delay(300);
    DBLN("setup() complete");
}

void loop()
{
    DB("millis()=");
    DB(millis());
    DB(" offset=");
    DB(_MillisOffsetMs);
    DB(" Millis()=");
    DBLN(Millis());
    delay(1000);
    addMillisOffset(0.3);
}

