#pragma once

#include <Arduino.h>
#include <Mode.h>

// A CounterMode prints a message to Serial every half a second
// with it's current counter value, and increments it.
class CounterMode : public Mode {
public:
    CounterMode(String id);
    void begin();
    void modeStart();
    void modeStop();
    void modeUpdate();

private:
    String _id;
    unsigned int _counter;

};

