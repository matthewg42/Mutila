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
    Serial.println(F("CounterMode::begin"));
}

void CounterMode::modeStart()
{
    Serial.println(F("CounterMode::modeStart"));
}

void CounterMode::modeStop()
{
    Serial.println(F("CounterMode::modeStop"));
}

void CounterMode::modeUpdate()
{
    // Do a thing
    Serial.print(F("CounterMode id="));
    Serial.print(_id);
    Serial.print(F(", counter="));
    Serial.println(_counter++);
}

