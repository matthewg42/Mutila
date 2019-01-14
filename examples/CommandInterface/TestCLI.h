#pragma once

#include <Arduino.h>
#include <CommandInterface.h>

class TestCLIClass : public CommandInterface 
{
public:
    TestCLIClass(String prompt);
    void begin(Stream& stream);
    void runCmd();

private:
    String _prompt;

};

extern TestCLIClass TestCLI;

