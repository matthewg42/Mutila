#pragma once

#define DFP_BUFLEN                  10
#define DFP_MIN_TIME_MS             20
#define DFP_RESP_TIMEOUT_MS         20

// Structure of the command packet
#define DFP_OFFSET_CMD              3
#define DFP_OFFSET_ARG              5
#define DFP_OFFSET_CKSUM            7

#include <Arduino.h>
#include <stdint.h>

/*! \brief A response to a query set to a DFPlayerMini object
 *
 * This object is returned when a query is sent to a DFPlayerMini object
 * It indicates the success of the query using the .status member, and
 * also contains the message type (which presumably should the same as
 * the command used in the query), and the argument (result) value, which
 * is always a uint16_t.
 */
struct DFPResponse {
    enum Status {
        Incomplete=0,     //!< Set when we start receiving, should not remain at end
        Ok=1,             //!< Messaged received and is valid
        Timeout=2,        //!< Message timed out (DFP_RESP_TIMEOUT_MS ms passed)
        SerialError=3,    //!< Indicates broken serial comms
        Invalid=4         //!< Response was not validated (bad cksum, header etc)
    };

    //! Default constructor - packet starts in Incomplete state
    DFPResponse() : status(Incomplete), messageType(0), arg(0) {;}

    // Data members
    Status status;
    uint8_t messageType;
    uint16_t arg;
};

/*! \brief Easy-to-use controller class for DFPlayer Mini devices
 *
 * This class implements some of the functionality of the 
 * DFPlayer_Mini_MP3 library, to control a DFPlayer Mini device.
 * It includes features which were not yet implemented in the 
 * DFPlayer_Mini_MP3 at time of writing, namely a mechanism to 
 * receive results of query calls to the device.
 *
 * The device is expected to be connected using serial and optionally
 * the BUSY line.  Serial comms are at 9600 baud.  The BUSY line is
 * pulled to ground when the DFPlayerMini device is playing an mp3
 * file.
 */
class DFPlayerMini {
public:

    /*! Command codes
     *
     * The DFPlayerMini's serial interface uses this set of command
     * codes to instruct the device to perform some action or reply
     * with some information. 
     */
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
        PlayTf          = 0x12, //!< Play track arg from (SD card)
        Stop            = 0x16, //!< Stop playback
        SingleLoop      = 0x19, //!< Loop track arg = boolean !state
        GetStatus       = 0x42, //!< Get some meaningless status code
        GetVolume       = 0x43, //!< Get volume setting
        GetUSum         = 0x47, //!< Get file count U
        GetTfSum        = 0x48, //!< Get file count Tf
        GetFlashSum     = 0x49, //!< Get file count Flash
        GetUCurrent     = 0x4B, //!< Get file current U
        GetTfCurrent    = 0x4C, //!< Get file current Tf
        GetFlashCurrent = 0x4D  //!< Get file current Flash [No response]
    };

    /*! Constructor
     * \param serial a software serial object set at 9600 baud connected 
     *        to the DFPlayerMini device
     * \param busyPin the pin on the arduino connected to the BUSY pin of 
     *        the DFPlayerMini. See the busy() documentation for more 
     *        details.
     */
    DFPlayerMini(Stream& serial, uint8_t busyPin=0);

    /*! Initialization
     * Sets up pin modes and resets state - typically called from begin()
     */
    void begin();

    /*! Send a command no response is expected
     * \param cmd The command to send
     * \param arg The argument to the command, if one is expected
     */
    void sendCmd(Cmd cmd, uint16_t arg=0);

    /*! Send a command and wait for a response
     * \param cmd The command to send
     * \param tries how many attempts will be made to get a valid result
     * \return a DFPResponse object with the results of the query. The .ok
     *         member will be false if the query failed to get a valid
     *         result (possible resons: timeout, bad serial comms etc.)
     */
    DFPResponse query(Cmd cmd, uint8_t tries=3);

    /*! Find out if a sound is playing
     * If the BUSY pin has been connected to the arduino and properly
     * set with the busyPin parameter to the DFPlayerMini constructor,
     * the value will be determined by analysing this pin state.
     *
     * If the busy pin was not passed when the DFPlayerMini was constructed,
     * a GetStatus query will be sent to the player and the result
     * analysed to determine the result. Note that the query method will
     * cause jitter in the audio playback, and takes longer to execute, 
     * so the BUSY pin method is recommended if there is a digital input
     * available.
     *
     * \return true if audio is currently playing, else false
     */
    bool busy();


private:
    DFPResponse _query(Cmd cmd);

    void resetSendBuf();
    void copyBigend(uint8_t *thebuf, uint16_t data);
    void fillChecksum();
    uint16_t calculateChecksum(uint8_t *thebuf);
    void serialCmd();

    Stream& _serial;
    uint8_t _busyPin;
    uint8_t _sendBuf[DFP_BUFLEN];
    unsigned long _lastCmdSent;

};


