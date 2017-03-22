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
    delay(3000);
    Serial.print("millis()=");
    Serial.print(millis());
    Serial.print(" Millis()=");
    Serial.println(Millis());
}

