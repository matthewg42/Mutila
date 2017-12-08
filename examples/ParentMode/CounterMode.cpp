#include <Arduino.h>
#include <MutilaDebug.h>
#include "CounterMode.h"

CounterMode::CounterMode(String id) :
    _id(id),
    _counter(0)
{
    // Only do a thing every 500ms - we're not barbarians
    setUpdatePeriod(500);
}

void CounterMode::begin()
{
    Serial.println("CounterMode::begin");
}

void CounterMode::modeStart()
{
    Serial.println("CounterMode::modeStart");
}

void CounterMode::modeStop()
{
    Serial.println("CounterMode::modeStop");
}

void CounterMode::modeUpdate()
{
    // Do a thing
    Serial.print("CounterMode id=");
    Serial.print(_id);
    Serial.print(", counter=");
    Serial.println(_counter++);
}

