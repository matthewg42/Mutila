#include <string.h>
#include <DFPlayerMini.h>
#include <MutilaDebug.h>
#include <Millis.h>

DFPlayerMini::DFPlayerMini(Stream& serial, const uint8_t busyPin) :
    _serial(serial),
    _busyPin(busyPin),
    _lastCmdSent(0)
{
}

void DFPlayerMini::begin(bool bootWait)
{
    pinMode(_busyPin, INPUT_PULLUP);
    resetSendBuf();
    if (bootWait) {
        delay(600);
    }
}

void DFPlayerMini::resetSendBuf()
{
    // Set up the send buffer with sentinels and such
    memset(&_sendBuf, 0, sizeof(uint8_t) * BufferLength);
    _sendBuf[0] = 0x7E;  // I assume these are like magic bytes to 
    _sendBuf[1] = 0xFF;  // idenfity this as a valid buffer?
    _sendBuf[2] = 0x06;  // payload length?
    _sendBuf[9] = 0xEF;  // send mark?
}

void DFPlayerMini::sendCmd(DFPlayerMini::Cmd cmd, uint16_t arg)
{
    _sendBuf[PacketOffsetCmd] = (uint8_t)cmd;
    copyBigend(_sendBuf+PacketOffsetArg, arg);
    fillChecksum();
    _serial.flush();
    serialCmd();
}

// This function is for debugging the content of the
// receive buffer, and is only used when DEBUG is set
void dumpBuf(uint8_t* buf, uint8_t ptr, bool ln=true)
{
    for (uint8_t i=0; i<DFPlayerMini::BufferLength; i++) {
        _DB(F(" 0x"));
        _DB(buf[i], HEX);
    }
    _DB(F(" ptr="));
    _DB(ptr);
    if (ln) {
        _DBLN(' ');
    }
}

DFPResponse DFPlayerMini::query(DFPlayerMini::Cmd cmd, uint8_t tries)
{
    for (uint8_t i=1; i<=tries; i++) {
        _DB(F("DFPlayerMini::query try "));
        _DB(i);
        _DB(F(" of "));
        _DBLN(tries);
        DFPResponse r = _query(cmd);
        if (r.status == DFPResponse::Ok) {
            return r;
        }
        // Add a random delay in case of sync problems
        delay(random(5));
    }
    _DB(F("DFPlayerMini::query FAILED all "));
    _DB(tries);
    _DBLN(F(" tries"));
    return DFPResponse();
}

DFPResponse DFPlayerMini::_query(DFPlayerMini::Cmd cmd)
{
    // This will hold our result. Note: response.status is Incomplete
    // after the response object has been constructed.
    DFPResponse response;

    // A buffer for the reply data
    uint8_t buf[BufferLength];
    memset(buf, 0, BufferLength*sizeof(uint8_t));

    // A pointer into the buffer where we will write incoming bytes
    uint8_t ptr = 0;

    millis_t startSend = Millis();
    sendCmd(cmd); 
    millis_t startRecv = Millis();

    // Populate buffer with response.
    while(true) {
        // Handle timeouts
        if (MillisSince(startRecv) > ResponseTimeoutMs) {
            response.status = DFPResponse::Timeout;
            break;
        }

        // Add bytes to buffer
        while (_serial.available() > 0 && ptr < BufferLength) {
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
        if (ptr == BufferLength) {
            break;
        }
    }
    // calculate how long comms took
    millis_t durationRecv = MillisSince(startRecv);

    _DB(F("DF RX:"));
    dumpBuf(buf, ptr, false);
    _DB(F(" send="));
    _DB(MillisSince(startRecv, startSend));
    _DB(F("ms, recv="));
    _DB(durationRecv);
    _DB(F("ms "));

    // flush the serial buffers just in case of junk
    _serial.flush();

    // put results into response object
    response.messageType = buf[PacketOffsetCmd];
    uint8_t* aptr = (uint8_t*)(&(response.arg));
    aptr[0] = buf[PacketOffsetArg+1];
    aptr[1] = buf[PacketOffsetArg];

    // Validate the packet
    uint16_t cksum = calculateChecksum(buf);
    // check the terminator looks OK
    if (buf[0] != 0x7E || buf[1] != 0xFF || buf[9] != 0xEF) {
        _DBLN(F("ERR: head/term"));
        response.status = DFPResponse::Invalid;
    } else if (*((uint8_t*)&cksum) != buf[PacketOffsetCkSum+1] || *(1+(uint8_t*)&cksum) != buf[PacketOffsetCkSum]) {
        response.status = DFPResponse::Invalid;
        _DBLN(F("ERR: cksum"));
    } else {
        // OK, we have a valid response
        response.status = DFPResponse::Ok;
        _DBLN(F("VALID"));
    }
    return response;
}

bool DFPlayerMini::busy()
{
    if (_busyPin != 0) {
        return !digitalRead(_busyPin);
    } else {
        DFPResponse r = query(DFPlayerMini::GetStatus);
        return r.arg != 512; // Not certain about this, but it seems to work...
    }
}

void DFPlayerMini::copyBigend(uint8_t *dst, uint16_t value)
{
    uint8_t* dp = (uint8_t*)dst;
    uint8_t* vp = (uint8_t*)&value;
    dp[0] = vp[1];
    dp[1] = vp[0];
}

void DFPlayerMini::fillChecksum()
{
    uint16_t checksum = calculateChecksum(_sendBuf);
    copyBigend(_sendBuf+PacketOffsetCkSum, checksum); 
}

uint16_t DFPlayerMini::calculateChecksum(uint8_t *thebuf) {
    uint16_t sum = 0;
    for (uint8_t i=1; i<PacketOffsetCkSum; i++) {
        sum += thebuf[i];
    }
    return -sum;
}

void DFPlayerMini::serialCmd()
{
    // wait until some short time has passed since the last command
    // so the DFPlayer Mini has had a chance to process it...
    while (MillisSince(_lastCmdSent) < MinimumTimeMs) {
        delay(1);
    }
    _DB(F("DF TX:"));
    for (uint8_t i=0; i<BufferLength; i++) {
        _DB(F(" 0x"));
        _DB(_sendBuf[i],HEX);
    }
    _DBLN(' ');
    _lastCmdSent = Millis();
    for (uint8_t i=0; i<BufferLength; i++) {
        _serial.write(_sendBuf[i]);
    }
}

bool DFPlayerMini::check()
{
    DFPResponse r = query(DFPlayerMini::GetStatus);
    return r.status == DFPResponse::Ok;
}


