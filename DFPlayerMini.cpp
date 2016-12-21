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

// This function is for debugging the content of the
// receive buffer, and is only used when DEBUG is set
dumpBuf(uint8_t* buf, uint8_t ptr, bool ln=true)
{
    for (uint8_t i=0; i<DFP_BUFLEN; i++) {
        DB(F(" 0x"));
        DB(buf[i], HEX);
    }
    DB(F(" ptr="));
    DB(ptr);
    if (ln)
        DBLN(' ');
}

DFPResponse DFPlayerMini::query(uint8_t cmd, uint8_t tries)
{
    for (uint8_t i=1; i<=tries; i++) {
        DB(F("DFPlayerMini::query try "));
        DB(i);
        DB(F(" of "));
        DBLN(tries);
        DFPResponse r = _query(cmd);
        if (r.status == DFPResponse::Ok) {
            return r;
        }
        // Add a random delay in case of sync problems
        delay(random(5));
    }
    DB(F("DFPlayerMini::query FAILED all "));
    DB(tries);
    DBLN(F(" tries"));
}

DFPResponse DFPlayerMini::_query(uint8_t cmd)
{
    // This will hold our result. Note: response.status is Incomplete
    // after the response object has been constructed.
    DFPResponse response;

    // A buffer for the reply data
    uint8_t buf[DFP_BUFLEN];
    memset(buf, 0, DFP_BUFLEN*sizeof(uint8_t));

    // A pointer into the buffer where we will write incoming bytes
    uint8_t ptr = 0;

    unsigned long startSend = millis();
    sendCmd(cmd); 
    unsigned long startRecv = millis();
    // Populate buffer with response.
    while(true) {
        // Handle timeouts
        if (millis() > startRecv + DFP_RESP_TIMEOUT_MS) {
            response.status = DFPResponse::Timeout;
            break;
        }

        // Add bytes to buffer
        while (_serial.available() > 0 && ptr < DFP_BUFLEN) {
            int c = _serial.read();
            if (c<0) {
                response.status = DFPResponse::SerialError;
                break;
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

        // We have a full buffer with the proper header - continue
        // to the next step: validation of the message
        if (ptr == DFP_BUFLEN) {
            break;
        }
    }
    // calculate how long comms took
    unsigned long durationRecv = millis() - startRecv;
    DB(F("DF RX "));
    dumpBuf(buf, ptr, false);
    DB(F(" send="));
    DB(startRecv - startSend);
    DB(F("ms, recv="));
    DB(durationRecv);
    DB(F("ms "));

    // Validate the packet
    uint16_t cksum = calculateChecksum(buf);
    // check the terminator looks OK
    if (buf[0] != 0x7E || buf[1] != 0xFF || buf[9] != 0xEF) {
        DBLN(F("ERR: head/term"));
        response.status = DFPResponse::Invalid;
        return response;
    } else if (*((uint8_t*)&cksum) != buf[DFP_OFFSET_CKSUM+1] || *(1+(uint8_t*)&cksum) != buf[DFP_OFFSET_CKSUM]) {
        response.status = DFPResponse::Invalid;
        DBLN(F("ERR: cksum"));
        return response;
    } else {
        // OK, we have a valid response
        response.status = DFPResponse::Ok;
        DBLN(F("VALID"));
    }
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



