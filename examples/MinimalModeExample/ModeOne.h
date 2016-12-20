#pragma once

#include <Mode.h>

class ModeOne : public Mode {
public:
    ModeOne();
    void start();
    void stop();
    void update();

private:
    unsigned long _last;

};

