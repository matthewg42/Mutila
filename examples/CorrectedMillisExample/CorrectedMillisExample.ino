#include <Arduino.h>
#include <Millis.h>

void setup()
{
    Serial.begin(115200);
    delay(300);
    Serial.println("setup end");
}

void loop()
{
    Serial.print("millis()=");
    Serial.print(millis());
    Serial.print(" offset=");
    Serial.print(_MillisOffsetMs);
    Serial.print(" Millis()=");
    Serial.println(Millis());
    delay(1000);
    addMillisOffset(0.3);
}

