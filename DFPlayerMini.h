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
        Next            = 0x01, //!< Play next track
        Prev            = 0x02, //!< Play previous track
        PlayPhysical    = 0x03, //!< Play track arg
        SetVolume       = 0x06, //!< Set volume to arg (0-30)
        SetEqalizer     = 0x07, //!< Set EQ, arg 0-5 (normal=0, pop, rock, jazz, classical, bass) 
        SetDevice       = 0x09, //!< Set device, arg 1-5 (U, SD, AUX, SLEEP, FLASH)
        Sleep           = 0x0A, //!< Enter low power sleep mode
        Reset           = 0x0C, //!< Exit sleep mode
        Play            = 0x0D, //!< Play track arg
        Pause           = 0x0E, //!< Pause playback
        PlayTfMp3       = 0x12, //!< Play track arg from Tf
        Stop            = 0x16, //!< Stop playback
        SingleLoop      = 0x19, //!< Loop track arg = boolean !state
        GetStatus       = 0x42, //!< Get some meaningless status code
        GetVolume       = 0x43, //!< Get volume setting
        GetUSum         = 0x47, //!< Get file count U
        GetTfSum        = 0x48, //!< Get file count Tf
        GetFlashSum     = 0x49, //!< Get file count Flash
        GetUCurrent     = 0x4B, //!< Get file current U
        GetTfCurrent    = 0x4C, //!< Get file current Tf
        GetFlashCurrent = 0x4D  //!< Get file current Flash
    };

    //! Constructor
    DFPlayerMini(Stream& serial);

    //! Send a command no response is expected
    void sendCmd(uint8_t cmd, uint16_t arg=0);

    //! Send a command and wait for a response
    //! Note: test DFPResponse.ok to check if it worked!
    DFPResponse query(uint8_t cmd, uint16_t arg=0);

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


