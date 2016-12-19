#include <Arduino.h>
#include "DualButton.h"

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
    Serial.println("setup end");
}

void loop()
{
    MyButton.update();
    if (millis() > next) {
        next = millis() + OUTPUT_MS;
        Serial.print("DualButton: pushed=");
        Serial.print(MyButton.pushed());
        Serial.print(" tapped=");
        Serial.print(MyButton.tapped());
        Serial.print(" held=");
        Serial.print(MyButton.held());
        Serial.print(" repeat=");
        Serial.println(MyButton.repeat());
    }
}


