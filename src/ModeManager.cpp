#include <MutilaDebug.h>
#include "ModeManager.h"

ModeManagerClass::ModeManagerClass() :
    currentMode(NULL)
{
}

void ModeManagerClass::begin(Mode* initialMode)
{
    DBLN(F("ModeManager::begin"));
    switchMode(initialMode);
}

void ModeManagerClass::update()
{
    if (currentMode != NULL) {
        currentMode->update();
    }
}

void ModeManagerClass::switchMode(Mode* newMode, bool force)
{
    if ((newMode != currentMode) || force) {
        if (currentMode != NULL) {
            currentMode->stop();
        }   
        currentMode = newMode;
        currentMode->start();
    }
}

bool ModeManagerClass::modeFinished()
{
    if (currentMode != NULL) {
        return currentMode->isFinished();
    } else {
        return false;
    }
}

