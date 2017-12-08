#include <Arduino.h>
#include <DigitalInputButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

#if defined(ARDUINO_ESP8266_NODEMCU) 
const uint8_t ButtonPin = D1;
#else
const uint8_t ButtonPin = 6;
#endif

const uint8_t LedPin = LED_BUILTIN;
uint32_t LastDb = 0;

DigitalInputButton Button(ButtonPin);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nS:setup");
    Button.begin();
    pinMode(LedPin, OUTPUT);
    // Show we can handle Millis wrap
    addMillisOffset(0xFFFFF000);
    // Settle down
    delay(300);
    Serial.println("E:setup");
}

void loop()
{
    bool isOn = Button.on();
    digitalWrite(LedPin, isOn);
    if (DoEvery(200, LastDb)) {
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" button value=");
        Serial.println(isOn);
    }
}

