#include <Arduino.h>
#include <MutilaDebug.h>
#include "ModeA2.h"
#include "ButtonA.h"

// Our global instance of the mode...
ModeA2_ ModeA2;

ModeA2_::ModeA2_() :
    counter(0)
{
    // Only do a thing every 500ms - we're not barbarians
    setUpdatePeriod(500);
}

void ModeA2_::begin()
{
    DBLN(F("ModeA2::begin"));
}

void ModeA2_::modeStart()
{
    DBLN(F("ModeA2::modeStart"));
}

void ModeA2_::modeStop()
{
    DBLN(F("ModeA2::modeStop"));
}

void ModeA2_::modeUpdate()
{
    // Show we're active
    DB(F("ModeA2 counter="));
    DBLN(counter++);
}

