#include <Arduino.h>
#include <DualButton.h>
#include <Millis.h>
#include <MutilaDebug.h>

#define BUT1_PIN 2
#define BUT2_PIN 3
#define OUTPUT_MS 50

// One button with LOW == pushed
DebouncedButton Button1(BUT1_PIN);

// And another button with HIGH == pushed
DebouncedButton Button2(BUT2_PIN, false);

// If either is pushed, the DualButton will register a press
DualButton MyButton(&Button1, &Button2);

unsigned long next = OUTPUT_MS;

void setup()
{
    Serial.begin(115200);
    MyButton.begin();
    delay(300);
    DBLN("setup() complete");
}

void loop()
{
    MyButton.update();
    if (Millis() > next) {
        next = Millis() + OUTPUT_MS;
        DB("DualButton: pushed=");
        DB(MyButton.pushed());
        DB(" tapped=");
        DB(MyButton.tapped());
        DB(" held=");
        DB(MyButton.held());
        DB(" repeat=");
        DBLN(MyButton.repeat());
    }
}


