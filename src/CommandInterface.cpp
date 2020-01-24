#include "MutilaDebug.h"
#include "CommandInterface.h"

CommandInterface::CommandInterface(uint8_t maxCmdLen) :
    echo(true),
    _stream(NULL),
    _maxLen(maxCmdLen),
    _idx(0),
    _buf(NULL)
{
    _buf = new char[_maxLen];
}

CommandInterface::~CommandInterface()
{
    if (_buf) {
        delete _buf;
        _buf = NULL;
    }
}

void CommandInterface::begin(Stream& stream)
{
    clearBuf();
    _stream = &stream;
    DBLN(F("CommandInterface::begin"));
}

void CommandInterface::clearBuf()
{
    if (_buf == NULL) return;
    memset(_buf, 0, sizeof(char) * _maxLen);
    _idx = 0;
}

void CommandInterface::update()
{
    if (_stream == NULL || _buf == NULL) return;
    while (_stream->available()) {
        int c = _stream->read();
        if (c < 0) {
            return;
        } else if (c == '\n' || c == '\r') {
            if (echo) {
                _stream->write('\n');
            }
            runCmd();
            clearBuf();
        } else if (_idx > 0 && (c == '\b' || c == 0x7F)) {
            // backspace
            _stream->write("\b \b");
            _buf[--_idx] = '\0';
        } else if (c >= ' ' && c <= '~' && _idx < _maxLen) {
            _buf[_idx++] = (char)c;
            if (echo) {
                _stream->write((char)c);
            }
        }
    }
}


