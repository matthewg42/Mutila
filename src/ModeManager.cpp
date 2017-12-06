#include <MutilaDebug.h>
#include "ModeManager.h"

ModeManager::ModeManager() :
    currentMode(NULL)
{
}

void ModeManager::begin(Mode* initialMode)
{
    DBLN(F("ModeManager::begin"));
    switchMode(initialMode);
}

void ModeManager::update()
{
    if (currentMode != NULL) {
        currentMode->update();
    }
}

void ModeManager::switchMode(Mode* newMode, bool force)
{
    if ((newMode != currentMode) || force) {
        if (currentMode != NULL) {
            currentMode->stop();
        }   
        currentMode = newMode;
        currentMode->start();
    }
}

bool ModeManager::modeFinished()
{
    if (currentMode != NULL) {
        return currentMode->isFinished();
    } else {
        return false;
    }
}

