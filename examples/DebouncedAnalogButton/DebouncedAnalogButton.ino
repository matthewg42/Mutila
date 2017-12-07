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
    Serial.println("setup() complete");
}

void loop() 
{
    Button.update();
    if (DoEvery(100, LastDb)) {
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" analog value=");
        Serial.print(analogRead(A0));
        Serial.print(" logical button value=");
        Serial.print(Button.on());
        Serial.print(" tapped=");
        Serial.print(Button.tapped());
        Serial.print(" repeat=");
        Serial.print(Button.repeat());
        Serial.print(" held=");
        Serial.println(Button.held());
    }
}

