#include <Arduino.h>
#include <DualButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

#if defined(ARDUINO_ESP8266_NODEMCU) 
const uint8_t Button1Pin = D1;
const uint8_t Button2Pin = D2;
#else
const uint8_t Button1Pin = 6;
const uint8_t Button2Pin = 5;
#endif

const uint8_t OutputMs = 100;
uint32_t LastDb = 0;

// One button with LOW == pushed
DebouncedButton Button1(Button1Pin);

// And another button with HIGH == pushed
DebouncedButton Button2(Button2Pin);

// If either is pushed, the DualButton will register a press
DualButton MyButton(&Button1, &Button2);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");
    MyButton.begin();
    // Show we can handle Millis wrap
    addMillisOffset(0xFFFFF000);
    delay(300);
    Serial.println("setup() end");
}

void loop()
{
    MyButton.update();
    if (DoEvery(OutputMs, LastDb)) {
        Serial.print("Millis=0x");
        Serial.print(Millis());
        Serial.print(" DualButton: pushed=");
        Serial.print(MyButton.pushed());
        Serial.print(" tapped=");
        Serial.print(MyButton.tapped());
        Serial.print(" held=");
        Serial.print(MyButton.held());
        Serial.print(" repeat=");
        Serial.println(MyButton.repeat());
    }
}


