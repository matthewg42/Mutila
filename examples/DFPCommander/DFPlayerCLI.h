#pragma once

#include <Arduino.h>
#include <CommandInterface.h>

class DFPlayerCLIClass : public CommandInterface 
{
public:
    DFPlayerCLIClass(String prompt);
    void begin(Stream& stream);
    void runCmd();
    void busy();
    void count();
    void play(int track);
    void query();
    void reset();
    void sleep();
    void volume(int volume);
    void wake();

private:
    String _prompt;

};

extern DFPlayerCLIClass DFPlayerCLI;

