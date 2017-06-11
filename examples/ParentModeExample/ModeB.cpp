#include <Arduino.h>
#include <MutilaDebug.h>
#include "ModeB.h"
#include "ButtonA.h"

// Our global instance of the mode...
ModeB_ ModeB;

ModeB_::ModeB_() :
    counter(0)
{
    // Only do a thing every 500ms - we're not barbarians
    setUpdatePeriod(500);
}

void ModeB_::begin()
{
    DBLN(F("ModeB::begin"));
}

void ModeB_::modeStart()
{
    DBLN(F("ModeB::modeStart"));
}

void ModeB_::modeStop()
{
    DBLN(F("ModeB::modeStop"));
}

void ModeB_::modeUpdate()
{
    // Show we're active
    DB(F("ModeB counter="));
    DBLN(counter++);
}

