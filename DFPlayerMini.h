#pragma once

#define DFP_BUFLEN                  10
#define DFP_CMD_NEXT                0x01
#define DFP_CMD_PLAY_N              0x12

// Structure of the command packet
#define DFP_OFFSET_CMD              3
#define DFP_OFFSET_ARG              5
#define DFP_OFFSET_CKSUM            7

#include <Arduino.h>
#include <stdint.h>

/*! \brief Easy-to-use controller class for DFPlayer Mini devices
 * This class implements some of the functionality of the 
 * DFPlayer_Mini_MP3 library, to control a DFPlayer Mini device.
 * The device is expected to be connected using serial, which must
 * be at 9600 baud.  SoftSerial works just fine.
 */
class DFPlayerMini {
public:
    DFPlayerMini(Stream& serial);

    //! Set volume
    //! \param v the volume in range 0 to 30.
    void setVolume(uint8_t v);

    //! Play the next track
    void next();

    //! Play track by number
    //! \param n the number of the track to play.
    void play(uint16_t n);

private:
    void resetSendBuf();
    void sendCmd(uint8_t cmd, uint16_t arg=0);
    void copyBigend(uint8_t *thebuf, uint16_t data);
    void fillChecksum();
    uint16_t calculateChecksum(uint8_t *thebuf);
    void serialCmd();

    Stream& _serial;
    uint8_t _sendBuf[DFP_BUFLEN];

};


