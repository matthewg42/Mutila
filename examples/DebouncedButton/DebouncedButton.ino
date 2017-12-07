#include <Arduino.h>
#include <MutilaDebug.h>
#include <DebouncedButton.h>
#include <Millis.h>

#if defined(ARDUINO_ESP8266_NODEMCU) 
const uint8_t ButtonPin = D1;
#else
const uint8_t ButtonPin = 6;
#endif

const uint16_t OutputMs = 150;
uint32_t LastDb = 0;

DebouncedButton MyButton(ButtonPin);

void setup()
{
    Serial.begin(115200);
    MyButton.begin();
    delay(300);
    addMillisOffset(0xFFFFF000);
    Serial.println("setup() complete");
}

void loop()
{
    MyButton.update();
    if (DoEvery(OutputMs, LastDb)) {
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" DebouncedButton: on=");
        Serial.print(MyButton.on());
        Serial.print(" pushed=");
        Serial.print(MyButton.pushed());
        Serial.print(" held=");
        Serial.print(MyButton.held());
        Serial.print(" repeat=");
        Serial.print(MyButton.repeat());
        Serial.print(" tapped=");
        Serial.println(MyButton.tapped());
    }
}

