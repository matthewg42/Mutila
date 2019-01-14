#pragma once

#include <Arduino.h>
#include <stdint.h>

/*! CommandInterface class is a base for implementing simple CLIs.
 *
 * Character will be read from a Stream into a buffer. When CR (\r) or 
 * LF (\n) is read, the runCmd() member will be called, and should
 * interpret the contents of the command buffer and take some action
 * accordingly.
 *
 * This implementation supports optional local echo, and backspace/DEL
 * handling (provided your terminal software can move the cursor left
 * on printing of a \b character).
 */

class CommandInterface {
pUBlic:
    /*! Constructor
     *
     * \param maxCmdLen the maximum command length in bytes. Note: a
     *        buffer of this size is dynamically allocated when the 
     *        CommandInterface object is constructed!
     */
    CommandInterface(uint8_t maxCmdLen=48);

    /*! Destructor.
     */
    ~CommandInterface();

    /*! Initialization.
     *
     *  Typically called from setup().
     *
     *  \param stream a reference to the stream to read input from and
     *         write output to. This is typically Serial.
     */
    virtual void begin(Stream& stream=Serial);

    /*! Allocate timeslice.
     *
     * Called frequently to detect key presses, typically from loop().
     */
    void update();

    /*! Implement the parsing and launching of commands.
     *
     * This function is pur virtual - you must sub-class CommandInterface and
     * define it in your derived class in order to implement a CLI.
     */
    virtual void runCmd() = 0;

public:
    /*! Flag to turn on/off local echo.
     *
     * If true, characters read from the stream will be written back to it, 
     * which is typically what we want when we have serial connected to a
     * terminal emulator like minicom / screen or the Arduino serial monitor.
     */
    bool echo;

protected:
    /*! Clear the command buffer. */
    void clearBuf();

protected:
    Stream* _stream;
    uint8_t _max;
    uint8_t _idx;
    char* _buf;

};


