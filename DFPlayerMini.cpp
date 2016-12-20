#include <string.h>
#include <DFPlayerMini.h>
#include <MutilaDebug.h>

DFPlayerMini::DFPlayerMini(Stream& serial) :
    _serial(serial)
{
    resetSendBuf();
}

void DFPlayerMini::resetSendBuf()
{
    // Set up the send buffer with sentinels and such
    memset(&_sendBuf, 0, sizeof(uint8_t) * DFP_BUFLEN);
    _sendBuf[0] = 0x7E;  // I assume these are like magic bytes to 
    _sendBuf[1] = 0xFF;  // idenfity this as a valid buffer?
    _sendBuf[2] = 0x06;  // payload length?
    _sendBuf[9] = 0xEF;  // send mark?
}

void DFPlayerMini::setVolume(uint8_t v)
{
    DB(F("DFPlayerMini::setVolume "));
    DBLN(v);
}

void DFPlayerMini::next()
{
    DBLN(F("DFPlayerMini::next "));
    sendCmd(DFP_CMD_NEXT);
}

void DFPlayerMini::play(uint16_t n)
{
    DB(F("DFPlayerMini::play "));
    DBLN(n);
    sendCmd(DFP_CMD_PLAY_N, n);
}

void DFPlayerMini::sendCmd(uint8_t cmd, uint16_t arg)
{
    _sendBuf[DFP_OFFSET_CMD] = cmd;
    copyBigend(_sendBuf+DFP_OFFSET_ARG, arg);
    fillChecksum();
    serialCmd();
}

void DFPlayerMini::copyBigend(uint8_t *buf, uint16_t i)
{
    *buf = (uint8_t)(i>>8);
    *(buf+1) = (uint8_t)i;
}

void DFPlayerMini::fillChecksum()
{
    uint16_t checksum = calculateChecksum(_sendBuf);
    copyBigend(_sendBuf+DFP_OFFSET_CKSUM, checksum); 
}

uint16_t DFPlayerMini::calculateChecksum(uint8_t *thebuf) {
    uint16_t sum = 0;
    for (uint8_t i=1; i<DFP_OFFSET_CKSUM; i++) {
        sum += thebuf[i];
    }
    return -sum;
}

void DFPlayerMini::serialCmd()
{
    Serial.print("SEND:");
    for (uint8_t i=0; i<DFP_BUFLEN; i++) {
        Serial.print(" 0x");
        Serial.print(_sendBuf[i],HEX);
        _serial.write(_sendBuf[i]);
    }
    Serial.println(' ');
}



