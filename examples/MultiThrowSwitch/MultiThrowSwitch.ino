#include <Arduino.h>
#include <MutilaDebug.h>
#include <MultiThrowSwitch.h>
#include <Millis.h>
#include "TestBoardPins.h"

const uint8_t SwitchPins[] = {
#if defined(ARDUINO_ESP8266_NODEMCU) 
    // The NodeMCU just doesn't have enough pins!
    Button1Pin, 
    Button2Pin 
#else 
    Button1Pin, 
    Button2Pin, 
    Button3Pin
#endif
};

const uint16_t OutputPeriodMs = 150;
millis_t LastOutputMs = 0;

MultiThrowSwitch MySwitchWithOff(sizeof(SwitchPins), SwitchPins, true);
MultiThrowSwitch MySwitchNoOff(sizeof(SwitchPins), SwitchPins, false);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    // Initialize switch objects
    MySwitchWithOff.begin();
    MySwitchNoOff.begin(1);

    Serial.println("setup() end");
}

void loop()
{
    MySwitchWithOff.update();
    MySwitchNoOff.update();
    if (DoEvery(OutputPeriodMs, LastOutputMs)) {
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" MySwitchWithOff position=");
        Serial.print(MySwitchWithOff.position());
        Serial.print(" MySwitchNoOff position=");
        Serial.println(MySwitchNoOff.position());
    }
}

