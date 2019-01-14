#include <MutilaDebug.h>
#include "TestCLI.h"

TestCLIClass::TestCLIClass(String prompt) :
    CommandInterface(48)
{
    _prompt = prompt;
}

void TestCLIClass::begin(Stream& stream)
{
    CommandInterface::begin(stream);
    DBLN(F("TestCLIClass::begin"));
    _stream->print(_prompt);
}

void TestCLIClass::runCmd()
{
    uint8_t i;
    String cmd;
    for (i = 0; i < _maxLen && _buf[i] != ' ' && _buf[i] != '\0'; i++) {
        cmd += _buf[i];
    }
    while (_buf[i] == ' ') { ++i; }
    
    if (cmd == "help") {
        _stream->println(F("Commands:"));
        _stream->println(F("help       - this cruft"));
        _stream->println(F("hi [name]  - say hello"));
        _stream->println(F("bye [name] - say goodbye"));
    } else if (cmd == "hi") {
        _stream->print(F("Well hello there, '"));
        _stream->print(_buf + i);
        _stream->println('\'');
    } else if (cmd == "bye") {
        _stream->print(F("Goodbye, '"));
        _stream->print(_buf + i);
        _stream->println('\'');
    } else {
        _stream->print(F("unknown command: '"));
        _stream->print(_buf);
        _stream->println(F("', try 'help'"));
    }
    
    _stream->print(_prompt);
}

TestCLIClass TestCLI("Bananas> ");

