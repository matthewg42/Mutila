#include <string.h>
#include <DFPlayerMini.h>
#include <MutilaDebug.h>

DFPlayerMini::DFPlayerMini(Stream& serial) :
    _serial(serial),
    _lastCmdSent(0)
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

void DFPlayerMini::sendCmd(uint8_t cmd, uint16_t arg)
{
    _sendBuf[DFP_OFFSET_CMD] = cmd;
    copyBigend(_sendBuf+DFP_OFFSET_ARG, arg);
    fillChecksum();
    serialCmd();
}

dumpBuf(uint8_t* buf, uint8_t ptr)
{
    DB(F("ptr="));
    DB(ptr);
    DB(F(" buf:"));
    for (uint8_t i=0; i<DFP_BUFLEN; i++) {
        DB(F(" 0x"));
        DB(buf[i], HEX);
    }
    DBLN(' ');
}

DFPResponse DFPlayerMini::fetch(uint8_t cmd, uint16_t arg)
{
    DFPResponse response;

    // wait for response...
    uint8_t buf[DFP_BUFLEN];
    memset(buf, 0, DFP_BUFLEN*sizeof(uint8_t));
    uint8_t ptr = 0;
    unsigned long start = millis();
    sendCmd(cmd, arg);
    while(true) {
        if (millis() > start + DFP_RESP_TIMEOUT_MS) {
            DB(F("WARN: timeout at start+"));
            DB(millis() - start);
            DB(' ');
            dumpBuf(buf, ptr);
            return response;
        }
        while (_serial.available() > 0 && ptr < DFP_BUFLEN) {
            int c = _serial.read();
            if (c<0) {
                DB(F("WARN: serial err "));
                dumpBuf(buf, ptr);
                return response;
            }

            if (ptr == 0 && c != 0x7E) {
                // skip until we see the start of a proper response
            } else if (ptr == 1 && c != 0xFF) {
                // not proper header, reset
                ptr = 0;
                buf[0] = 0;
            } else {
                // looking good - append to buffer
                buf[ptr++] = (uint8_t)c;
            }
        }
        if (ptr == DFP_BUFLEN) {
            break;
        }
    }

    DB(F("DF RX: "));
    dumpBuf(buf, ptr);
    // check the terminator looks OK
    if (buf[9] != 0xEF) {
        DBLN(F("DFPlayerMini WARN: bad resp"));
        return response;
    }
    // TODO: checksum validation
    
    // OK, we have a valid response
    response.ok = true;
    response.messageType = buf[DFP_OFFSET_CMD];
    uint8_t* aptr = (uint8_t*)(&(response.arg));
    aptr[0] = buf[DFP_OFFSET_ARG+1];
    aptr[1] = buf[DFP_OFFSET_ARG];
    return response;
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
    // wait until some short time has passed since the last command
    // so the DFPlayer Mini has had a chance to process it...
    while (millis() < _lastCmdSent + DFP_MIN_TIME_MS) {
        delay(1);
    }
    DB(F("DF TX:"));
    for (uint8_t i=0; i<DFP_BUFLEN; i++) {
        DB(F(" 0x"));
        DB(_sendBuf[i],HEX);
    }
    DBLN(' ');
    _lastCmdSent = millis();
    for (uint8_t i=0; i<DFP_BUFLEN; i++) {
        _serial.write(_sendBuf[i]);
    }
}



