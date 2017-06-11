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
    DBLN(F("CounterMode::begin"));
}

void CounterMode::modeStart()
{
    DBLN(F("CounterMode::modeStart"));
}

void CounterMode::modeStop()
{
    DBLN(F("CounterMode::modeStop"));
}

void CounterMode::modeUpdate()
{
    // Do a thing
    DB(F("CounterMode id="));
    DB(_id);
    DB(F(", counter="));
    DBLN(_counter++);
}

