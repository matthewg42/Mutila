#pragma once

#include <stdint.h>
#include <DFPlayerMini.h>

#define DFPR_SAY_BUF_SIZE           20

#define MP3_TRACK_ZERO              200
#define MP3_TRACK_TEN               210
#define MP3_TRACK_TWENTY            220
#define MP3_TRACK_THIRTY            221
#define MP3_TRACK_FOURTY            222
#define MP3_TRACK_FIFTY             223
#define MP3_TRACK_SIXTY             224
#define MP3_TRACK_SEVENTY           225
#define MP3_TRACK_EIGHTY            226
#define MP3_TRACK_NINETY            227
#define MP3_TRACK_HUNDRED           228
#define MP3_TRACK_THOUSAND          229
#define MP3_TRACK_MILLION           230
#define MP3_TRACK_BILLION           231
#define MP3_TRACK_TRILLION          232
#define MP3_TRACK_POINT             233
#define MP3_TRACK_MINUS             234
#define MP3_TRACK_HOUR              235
#define MP3_TRACK_HOURS             236
#define MP3_TRACK_MINUTE            237
#define MP3_TRACK_MINUTES           238
#define MP3_TRACK_SECOND            239
#define MP3_TRACK_SECONDS           240
#define MP3_TRACK_MILLISECOND       241
#define MP3_TRACK_MILLISECONDS      242
#define MP3_TRACK_AND               243

/*! \brief DFPlayerMini controller with numeric readout functions
 *
 */
class DFPReader : public DFPlayerMini {
public:

    /*! Constructor
     * \param serial a software serial object set at 9600 baud connected 
     *        to the DFPlayerMini device
     * \param busyPin the pin on the arduino connected to the BUSY pin of 
     *        the DFPlayerMini. See the busy() documentation for more 
     *        details.
     */
    DFPReader(Stream& serial, uint8_t busyPin=0);

    /* Initialize
     * Typically called from setup()
     */
    void begin();

    /*! Allocate Timeslice
     * Should be called frequently - typically from loop()
     */
    void update();

    /*! Queue up digits of a number to read
     * 
     */
    void readNumber(float number, uint8_t dp=0);

private:
    void resetReaderBuf();

    void appendElement(uint8_t value);
    void appendSubThousand(int num);
    void appendMagnitude(float* number, float magnitude, uint8_t magnitudeElement);

    // Some data for figuring out this pesky human speach stuff
    static const uint8_t SMALL_NUMBERS[];
    static const uint8_t TENS[];

    // Ring buffer
    uint8_t readerBuf[DFPR_SAY_BUF_SIZE];
    uint8_t headPtr;
    uint8_t tailPtr;

};


