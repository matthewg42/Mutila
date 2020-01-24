#include <Arduino.h>
#include <ToggleButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

#if defined(ARDUINO_ESP8266_NODEMCU) 
const uint8_t ButtonPin = D1;
#else
const uint8_t ButtonPin = 3;
#endif
const uint8_t LedPin = LED_BUILTIN;

const uint8_t OutputPeriodMs = 200;
millis_t LastOutputMs = 0;

ToggleButton MyButton(ButtonPin);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show that we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    // Initialize objects and pins
    MyButton.begin();
    pinMode(LedPin, OUTPUT);

    Serial.println("setup() complete");
}

void loop()
{
    MyButton.update();
    if (DoEvery(OutputPeriodMs, LastOutputMs)) {
        bool o = MyButton.on();
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" ToggleButton.on()=");
        Serial.println(o);
        digitalWrite(LedPin, o);
    }
}

