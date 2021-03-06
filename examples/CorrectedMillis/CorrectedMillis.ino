#include <Arduino.h>
#include <Millis.h>
#include <MutilaDebug.h>

/* Example showing how we can use Millis and AddMillisOffset to adjust 
 * for drift in millis() when interrupts are disabled 
 */

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");
    Serial.println("setup() end");
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
    AddMillisOffset(0.3);
}

