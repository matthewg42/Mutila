#include <ParentMode.h>

ParentMode::ParentMode()
{
    pMode = NULL;
}

void ParentMode::switchMode(Mode* newMode)
{
    if (pMode != NULL) {
        pMode->stop();
    }
    pMode = newMode;
    pMode->start();
}

