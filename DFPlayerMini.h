#pragma once

#define DFPLAYERMINI_BUFLEN 10

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

    //! Play track by number
    //! \param n the number of the track to play.
    void play(uint16_t n);

private:
    Stream& _serial;

};


