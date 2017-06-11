#include <Arduino.h>
#include <MutilaDebug.h>
#include "ModeA1.h"
#include "ButtonA.h"

// Our global instance of the mode...
ModeA1_ ModeA1;

ModeA1_::ModeA1_() :
    counter(0)
{
    // Only do a thing every 500ms - we're not barbarians
    setUpdatePeriod(500);
}

void ModeA1_::begin()
{
    DBLN(F("ModeA1::begin"));
}

void ModeA1_::modeStart()
{
    DBLN(F("ModeA1::modeStart"));
}

void ModeA1_::modeStop()
{
    DBLN(F("ModeA1::modeStop"));
}

void ModeA1_::modeUpdate()
{
    // Show we're active
    DB(F("ModeA1 counter="));
    DBLN(counter++);
}

