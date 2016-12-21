#pragma once

#define DFP_BUFLEN                  10
#define DFP_MIN_TIME_MS             10
#define DFP_RESP_TIMEOUT_MS         50

// Structure of the command packet
#define DFP_OFFSET_CMD              3
#define DFP_OFFSET_ARG              5
#define DFP_OFFSET_CKSUM            7

#include <Arduino.h>
#include <stdint.h>

struct DFPResponse {
    DFPResponse() : ok(false), messageType(0), arg(0) {;}
    bool ok;
    uint8_t messageType;
    uint16_t arg;
};

/*! \brief Easy-to-use controller class for DFPlayer Mini devices
 * This class implements some of the functionality of the 
 * DFPlayer_Mini_MP3 library, to control a DFPlayer Mini device.
 * The device is expected to be connected using serial, which must
 * be at 9600 baud.  SoftSerial works just fine.
 */
class DFPlayerMini {
public:
    enum Cmd {
        Undefined       = 0x00,
        Next            = 0x01,
        Prev            = 0x02,
        SetVolume       = 0x06,
        SetEqalizer     = 0x07,
        SetDevice       = 0x09,
        Sleep           = 0x0A,
        Reset           = 0x0C,
        PlayN           = 0x0D,
        Pause           = 0x0E,
        PlayNtfMp3      = 0x12,
        Stop            = 0x16,
        SingleLoop      = 0x19,
        GetStatus       = 0x42,
        GetVolume       = 0x43,
        GetUSum         = 0x47,
        GetTfSum        = 0x48,
        GetFlashSum     = 0x49,
        GetUCurrent     = 0x4B,
        GetTfCurrent    = 0x4C,
        GetFlashCurrent = 0x4D
    };

    //! Constructor
    DFPlayerMini(Stream& serial);

    //! Send a command no response is expected
    void sendCmd(uint8_t cmd, uint16_t arg=0);

    //! Send a command and wait for a response
    //! Note: test DFPResponse.ok to check if it worked!
    DFPResponse fetch(uint8_t cmd, uint16_t arg=0);

private:
    void resetSendBuf();
    void copyBigend(uint8_t *thebuf, uint16_t data);
    void fillChecksum();
    uint16_t calculateChecksum(uint8_t *thebuf);
    void serialCmd();

    Stream& _serial;
    uint8_t _sendBuf[DFP_BUFLEN];
    unsigned long _lastCmdSent;

};


