#include <Arduino.h>
#include <Millis.h>
#include <MutilaDebug.h>

/* Example showing how we can use Millis and addMillisOffset to adjust 
 * for drift in millis() when interrupts are disabled 
 */

void setup()
{
    Serial.begin(115200);
    delay(300);
    Serial.println("setup() complete");
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

