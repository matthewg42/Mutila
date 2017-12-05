#include <Arduino.h>
#include <DualButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t Button1Pin = 6;
const uint8_t Button2Pin = 5;
const uint8_t OutputMs = 50;
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
    MyButton.begin();
    // Show we can handle Millis wrap
    addMillisOffset(0xFFFFF000);
    delay(300);
    DBLN("setup() complete");
}

void loop()
{
    MyButton.update();
    if (DoEvery(OutputMs, LastDb)) {
        DB("Millis=0x");
        DB(Millis());
        DB(" DualButton: pushed=");
        DB(MyButton.pushed());
        DB(" tapped=");
        DB(MyButton.tapped());
        DB(" held=");
        DB(MyButton.held());
        DB(" repeat=");
        DBLN(MyButton.repeat());
    }
}


