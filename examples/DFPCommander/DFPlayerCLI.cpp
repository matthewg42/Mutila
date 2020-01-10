#include <MutilaDebug.h>
#include "DFPlayerCLI.h"
#include "Player.h"

DFPlayerCLIClass DFPlayerCLI("DfPlayerMini> ");

DFPlayerCLIClass::DFPlayerCLIClass(String prompt) :
    CommandInterface(48)
{
    _prompt = prompt;
}

void DFPlayerCLIClass::begin(Stream& stream)
{
    CommandInterface::begin(stream);
    DBLN(F("DFPlayerCLIClass::begin"));
    _stream->print(_prompt);
}

void DFPlayerCLIClass::runCmd()
{
    uint8_t i;
    String cmd;
    for (i = 0; i < _maxLen && _buf[i] != ' ' && _buf[i] != '\0'; i++) {
        cmd += _buf[i];
    }
    while (_buf[i] == ' ') { ++i; }
    
    if (cmd == "help" || cmd == "h" || cmd == "") {
        _stream->println(F("Commands (can use just first letter):"));
        _stream->println(F("help       - this cruft"));
        _stream->println(F("busy       - check busy status"));
        _stream->println(F("count      - print track count"));
        _stream->println(F("play *n*   - play track *n*"));
        _stream->println(F("query      - query status of DFPlayer Mini"));
        _stream->println(F("reset      - wake up from sleep"));
        _stream->println(F("sleep      - go to sleep (low power mode)"));
        _stream->println(F("volume *n* - set volume (0-15)"));
        _stream->println(F("wake       - wake up from sleep"));
    } else if (cmd == "busy" || cmd == "b") {
        busy();
    } else if (cmd == "count" || cmd == "c") {
        count();
    } else if (cmd == "play" || cmd == "p") {
        play(atoi(_buf + i));
    } else if (cmd == "query" || cmd == "q") {
        query();
    } else if (cmd == "reset" || cmd == "r") {
        reset();
    } else if (cmd == "sleep" || cmd == "s") {
        sleep();
    } else if (cmd == "volume" || cmd == "v") {
        volume(atoi(_buf + i));
    } else if (cmd == "wake" || cmd == "w") {
        wake();
    } else {
        _stream->print(F("unknown command: '"));
        _stream->print(_buf);
        _stream->println(F("', try 'help'"));
    }
    
    _stream->print(_prompt);
}

void DFPlayerCLIClass::busy()
{
    _stream->println(Player.busy() ? F("TRUE") : F("FALSE"));
}

void DFPlayerCLIClass::count()
{
    DFPResponse r;
    r = Player.query(DFPlayerMini::GetTfSum);
    if (r.status == DFPResponse::Ok) {
        _stream->println(r.arg);
    } else {
        _stream->println(F("ERR"));
    }
}

void DFPlayerCLIClass::play(int track)
{
    Player.sendCmd(DFPlayerMini::PlayTf, track);
}

void DFPlayerCLIClass::query() {
    DFPResponse r;
    r = Player.query(DFPlayerMini::GetVolume);
    _stream->print(F("Volume="));
    if (r.status == DFPResponse::Ok) { _stream->print(r.arg); }
    else { _stream->print(F("ERR")); }

    r = Player.query(DFPlayerMini::GetStatus);
    _stream->print(F(" Status="));
    if (r.status == DFPResponse::Ok) { _stream->print(r.arg); }
    else { _stream->print(F("ERR")); }

    r = Player.query(DFPlayerMini::GetUSum);
    _stream->print(F(" GetUSum="));
    if (r.status == DFPResponse::Ok) { _stream->print(r.arg); }
    else { _stream->print(F("ERR")); }

    r = Player.query(DFPlayerMini::GetTfSum);
    _stream->print(F(" GetTfSum="));
    if (r.status == DFPResponse::Ok) { _stream->print(r.arg); }
    else { _stream->print(F("ERR")); }

    r = Player.query(DFPlayerMini::GetFlashSum);
    _stream->print(F(" GetFlashSum="));
    if (r.status == DFPResponse::Ok) { _stream->print(r.arg); }
    else { _stream->print(F("ERR")); }

    r = Player.query(DFPlayerMini::GetUCurrent);
    _stream->print(F(" GetUCurrent=")); if (r.status == DFPResponse::Ok) { _stream->print(r.arg); }
    else { _stream->print(F("ERR")); }

    r = Player.query(DFPlayerMini::GetUCurrent);
    _stream->print(F(" GetTfCurrent="));
    if (r.status == DFPResponse::Ok) { _stream->print(r.arg);  }
    else { _stream->print(F("ERR")); }

    _stream->println();
}

void DFPlayerCLIClass::reset()
{
    Player.sendCmd(DFPlayerMini::Reset);
    delay(600);
}

void DFPlayerCLIClass::sleep()
{
    Player.sendCmd(DFPlayerMini::Sleep);
}

void DFPlayerCLIClass::volume(int volume)
{
    Player.sendCmd(DFPlayerMini::SetVolume, volume);
}

void DFPlayerCLIClass::wake()
{
    Player.sendCmd(DFPlayerMini::Wake);
}

