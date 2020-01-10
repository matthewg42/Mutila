#include <Arduino.h>
#include <DigitalInputButton.h>
#include <AnalogInputButton.h>
#include <DualInputButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

#if defined(ARDUINO_ESP8266_NODEMCU) 
const uint8_t DigitalInputButtonPin = D1;
#else
const uint8_t DigitalInputButtonPin = 9;
#endif

const uint8_t AnalogInputButtonPin = A5;
const uint8_t LedPin = LED_BUILTIN;
const uint16_t OutputPeriodMs = 200;
uint32_t LastOutputMs = 0;
bool previousValue = false;

DigitalInputButton Button1(DigitalInputButtonPin);
AnalogInputButton Button2(AnalogInputButtonPin);
DualInputButton CombinedButtonOr(Button1, Button2); // default is Or mode
DualInputButton CombinedButtonXor(Button1, Button2, DualInputButton::Xor);
DualInputButton CombinedButtonAnd(Button1, Button2, DualInputButton::And);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() begin");

    // We don't need to call begin() for Button1 and Button2
    // because CombinedButton.begin() will do it for us.
    CombinedButtonOr.begin();
    CombinedButtonXor.begin(false);
    CombinedButtonAnd.begin(false);

    pinMode(LedPin, OUTPUT);

    // Show we can handle Millis wrap
    AddMillisOffset(0xFFFFF000);

    // Settle down (analog inputs can be a bit weird for a short
    // time after power-up)
    delay(300);

    Serial.println("setup() end");
}

void loop()
{
    if (DoEvery(OutputPeriodMs, LastOutputMs)) {
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" Button1 on=");
        Serial.print(Button1.on());
        Serial.print(" Button2 on=");
        Serial.print(Button2.on());
        Serial.print(" CombinedButtonOr on=");
        Serial.print(CombinedButtonOr.on());
        Serial.print(" CombinedButtonXor on=");
        Serial.print(CombinedButtonXor.on());
        Serial.print(" CombinedButtonAnd on=");
        Serial.println(CombinedButtonAnd.on());
    }
}


