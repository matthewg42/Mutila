#include <DFPlayerMini.h>
#include <MutilaDebug.h>

DFPlayerMini::DFPlayerMini(Stream& serial) :
    _serial(serial)
{
}

void DFPlayerMini::setVolume(uint8_t v)
{
    DB(F("DFPlayerMini::setVolume "));
    DBLN(v);
}

void DFPlayerMini::play(uint16_t n)
{
    DB(F("DFPlayerMini::play "));
    DBLN(n);
}



