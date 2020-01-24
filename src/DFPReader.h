#pragma once

#include <stdint.h>
#include <Millis.h>
#include <DFPlayerMini.h>

/*! DFPlayerMini controller with numeric readout functions.
 *
 *  This class is intended for use with the samples in the audio/ directory of
 *  the main Mutila repository.  Copy these files to an SD card in a directory 
 *  called "mp3". 
 */
class DFPReader : public DFPlayerMini {
public:
    static const uint8_t PlaybackStartMs =   120;

    // Track file numbers
    static const uint8_t Mp3TrackZero =           200;
    static const uint8_t Mp3TrackTen =            210;
    static const uint8_t Mp3TrackTwenty =         220;
    static const uint8_t Mp3TrackThirty =         221;
    static const uint8_t Mp3TrackFourty =         222;
    static const uint8_t Mp3TrackFifty =          223;
    static const uint8_t Mp3TrackSixty =          224;
    static const uint8_t Mp3TrackSeventy =        225;
    static const uint8_t Mp3TrackEighty =         226;
    static const uint8_t Mp3TrackNinety =         227;
    static const uint8_t Mp3TrackHundred =        228;
    static const uint8_t Mp3TrackThousand =       229;
    static const uint8_t Mp3TrackMillion =        230;
    static const uint8_t Mp3TrackBillion =        231;
    static const uint8_t Mp3TrackTrillion =       232;
    static const uint8_t Mp3TrackPoint =          233;
    static const uint8_t Mp3TrackMinus =          234;
    static const uint8_t Mp3TrackYear =           235;
    static const uint8_t Mp3TrackYears =          236;
    static const uint8_t Mp3TrackMonth =          237;
    static const uint8_t Mp3TrackMonths =         238;
    static const uint8_t Mp3TrackWeek =           239;
    static const uint8_t Mp3TrackWeeks =          240;
    static const uint8_t Mp3TrackDay =            241;
    static const uint8_t Mp3TrackDays =           242;
    static const uint8_t Mp3TrackHour =           243;
    static const uint8_t Mp3TrackHours =          244;
    static const uint8_t Mp3TrackMinute =         245;
    static const uint8_t Mp3TrackMinutes =        246;
    static const uint8_t Mp3TrackSecond =         247;
    static const uint8_t Mp3TrackSeconds =        248;
    static const uint8_t Mp3TrackMillisecond =    249;
    static const uint8_t Mp3TrackMilliseconds =   250;
    static const uint8_t Mp3TrackAnd =            251;

public:
    /*! \enum PlaybackState.
     */
    enum PlaybackState {
        Idle,       //!< Reader is idle.
        Pending,    //!< Reader is not playing, but is waiting for an audio file to play.
        Playing     //!< Reader is playing an audio file.
    };

    /*! Constructor.
     *
     *  \param serial a software serial object set at 9600 baud connected 
     *         to the DFPlayerMini device.
     *  \param busyPin the pin on the arduino connected to the BUSY pin of 
     *         the DFPlayerMini. See the busy() documentation for more 
     *         details.
     */
    DFPReader(Stream& serial, DFPlayerMini::Cmd playCmd=DFPlayerMini::PlayTf, uint8_t busyPin=0, uint8_t readerBufferSize=30);

    /*! Destructor.
     */  
    ~DFPReader();

    /*! Initialize.
     *
     *  Typically called from setup().
     *
     *  \param bootWait if true, wait 600ms for the DFPlayer to boot.
     */
    void begin(bool bootWait=true);

    /*! Allocate Timeslice.
     *
     * Should be called frequently - typically from loop().
     */
    void update();

    /*! Queue up digits of a number to read.
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

    /*! Find out if still reading.
     *
     *  \return true if a sound is being played, or if there are still
     *          samples to play after the current sample (i.e. if we're
     *          still reading out a number), else return false
     */
    bool reading();

    /*! Stop playback and reset the run buffer to an empty state.
     */
    void resetReaderBuf();

    /*! Append a sample to play.
     *
     *  Add a sample to the end of the run buffer to play
     *  as soon as other elements in the buffer have been played.
     */
    bool appendElement(uint8_t value);

private:
    DFPlayerMini::Cmd _playCmd;

    void startPlayback(uint16_t track);

    /*! Get next playable element from buffer.
     *
     *  \return next element in buffer (FIFO style), or 0 if the buffer is empty.
     */
    uint8_t popElement();

    /*! Append a number to the queue, where the number is less than 1000.
     *
     *  \num an integer less than 1000
     */
    void appendSubThousand(int16_t num);

    /*! Append a magnitude to the queue.
     */
    void appendMagnitude(double* number, double magnitude, uint8_t magnitudeElement);

    // Some data for figuring out this pesky human speech stuff
    static const uint8_t SMALL_NUMBERS[];
    static const uint8_t TENS[];

    // Ring buffer
    const uint8_t readerBufSize;
    uint8_t *readerBuf;
    uint8_t tailPtr;
    uint8_t unplayedElements;

    millis_t lastPlayStart;
    PlaybackState playbackState;

};


