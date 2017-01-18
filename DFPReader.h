#pragma once

#include <stdint.h>
#include <DFPlayerMini.h>

#define DFPR_PLAYBACK_START_MS      100

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
#define MP3_TRACK_YEAR              235
#define MP3_TRACK_YEARS             236
#define MP3_TRACK_MONTH             237
#define MP3_TRACK_MONTHS            238
#define MP3_TRACK_WEEK              239
#define MP3_TRACK_WEEKS             240
#define MP3_TRACK_DAY               241
#define MP3_TRACK_DAYS              242
#define MP3_TRACK_HOUR              243
#define MP3_TRACK_HOURS             244
#define MP3_TRACK_MINUTE            245
#define MP3_TRACK_MINUTES           246
#define MP3_TRACK_SECOND            247
#define MP3_TRACK_SECONDS           248
#define MP3_TRACK_MILLISECOND       249
#define MP3_TRACK_MILLISECONDS      250
#define MP3_TRACK_AND               251

/*! \brief DFPlayerMini controller with numeric readout functions
 *
 * This class is intended for use with the samples in the audio/ directory of
 * the main Mutila repository.  Copy these files to an SD card in a directory 
 * called "mp3". 
 */
class DFPReader : public DFPlayerMini {
public:
    enum PlaybackState {
        Idle,
        Pending,
        Playing
    };

    /*! Constructor
     * \param serial a software serial object set at 9600 baud connected 
     *        to the DFPlayerMini device
     * \param busyPin the pin on the arduino connected to the BUSY pin of 
     *        the DFPlayerMini. See the busy() documentation for more 
     *        details.
     */
    DFPReader(Stream& serial, DFPlayerMini::Cmd playCmd=DFPlayerMini::PlayTf, uint8_t busyPin=0, uint8_t readerBufferSize=30);

    /*! Destructor
     */  
    ~DFPReader();

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
     * When called, the ring buffer is populated with the IDs of
     * samples which are required to read the number.  For example
     * if number=3.14159, and dp=2, the samples for "three", "point"
     * "one", and "four" would be appened to the ring buffer.
     *
     * During update(), samples are played in order such that they
     * do not overlap.
     */
    void readNumber(double number, uint8_t dp=0);

    /*! Find out if still reading
     * \return true if a sound is being played, or if there are still
     *         samples to play after the current sample (i.e. if we're
     *         still reading out a number), else return false
     */
    bool reading();

    /*! Stop playback and reset the run buffer to an empty state
     */
    void resetReaderBuf();

    /*! Append a sample to play
     * Add a sample to the end of the run buffer to play
     * as soon as other elements in the buffer have been played
     */
    bool appendElement(uint8_t value);

private:
    DFPlayerMini::Cmd _playCmd;

    void startPlayback(uint16_t track);

    //! Get next playable element from buffer
    //! \return next element in buffer (FIFO style), or 
    //!         0 if the buffer is empty.
    uint8_t popElement();

    void appendSubThousand(int num);
    void appendMagnitude(double* number, double magnitude, uint8_t magnitudeElement);

    // Some data for figuring out this pesky human speech stuff
    static const uint8_t SMALL_NUMBERS[];
    static const uint8_t TENS[];

    // Ring buffer
    const uint8_t readerBufSize;
    uint8_t *readerBuf;
    uint8_t tailPtr;
    uint8_t unplayedElements;

    unsigned long lastPlayStart;
    PlaybackState playbackState;

};


