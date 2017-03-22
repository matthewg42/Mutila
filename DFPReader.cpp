#include "MutilaDebug.h"
#include "DFPReader.h"
#include "Millis.h"

const uint8_t DFPReader::SMALL_NUMBERS[] = {
        MP3_TRACK_ZERO, MP3_TRACK_ZERO+1, MP3_TRACK_ZERO+2, MP3_TRACK_ZERO+3, 
        MP3_TRACK_ZERO+4, MP3_TRACK_ZERO+5, MP3_TRACK_ZERO+6, MP3_TRACK_ZERO+7, 
        MP3_TRACK_ZERO+8, MP3_TRACK_ZERO+9, MP3_TRACK_ZERO+10, MP3_TRACK_ZERO+11, 
        MP3_TRACK_ZERO+12, MP3_TRACK_ZERO+13, MP3_TRACK_ZERO+14, MP3_TRACK_ZERO+15,
        MP3_TRACK_ZERO+16, MP3_TRACK_ZERO+17, MP3_TRACK_ZERO+18, MP3_TRACK_ZERO+19
};

const uint8_t DFPReader::TENS[] = {
        0, 0, MP3_TRACK_TWENTY, MP3_TRACK_THIRTY, MP3_TRACK_FOURTY,
        MP3_TRACK_FIFTY, MP3_TRACK_SIXTY, MP3_TRACK_SEVENTY, 
        MP3_TRACK_EIGHTY, MP3_TRACK_NINETY
};

DFPReader::DFPReader(Stream& serial, DFPlayerMini::Cmd playCmd, uint8_t busyPin, uint8_t readerBufferSize) :
    DFPlayerMini(serial, busyPin),
    _playCmd(playCmd),
    readerBufSize(readerBufferSize)
{
    readerBuf = new uint8_t[readerBufSize];
}

DFPReader::~DFPReader()
{
    delete readerBuf;
}

void DFPReader::begin()
{
    DFPlayerMini::begin();
    resetReaderBuf();
    lastPlayStart = 0;
    playbackState = Playing; // we will let it reset itself, in case there is a track already playing...
}

void DFPReader::update()
{
    if (playbackState == Pending) {
        if (millis() - lastPlayStart >= DFPR_PLAYBACK_START_MS) {
            _DBLN(F("playbackState Pending -> Playing"));
            playbackState = Playing;
        }
    } else if (playbackState == Playing) {
        if (!busy()) {
            _DBLN(F("playbackState Playing -> Idle"));
            playbackState = Idle;
        }
    }

    if (unplayedElements > 0) {
        if (playbackState == Idle) {
            startPlayback(popElement());
        }
    }
}

void DFPReader::startPlayback(uint16_t track)
{
    _DB(F("DFPReader::startPlayback "));
    _DBLN(track);
    lastPlayStart = millis();
    playbackState = Pending;
    sendCmd(_playCmd, track);
}

void DFPReader::readNumber(double number, uint8_t dp)
{
    _DB(F("DFPReader::readNumber n="));
    _DB(number, 10);
    _DB(F(" dp="));
    _DB(dp);
    double integerPart, fractionalPart;
    double exp = pow(10, dp);
    number = round(number*exp) / exp;
    _DB(F(" rounded="));
    _DB(number, 10);
    fractionalPart = modf(number, &integerPart);
    _DB(F(" ip="));
    _DB(integerPart, 10);
    _DB(F(" fp="));
    _DBLN(fractionalPart, 10);

    if (integerPart < 0.0) {
        appendElement(MP3_TRACK_MINUS);
        integerPart = fabs(integerPart);
    }

    if (integerPart < 0.1) {
        appendElement(MP3_TRACK_ZERO);
    } else {
        appendMagnitude(&integerPart, 1000000000000.0, MP3_TRACK_TRILLION);
        appendMagnitude(&integerPart, 1000000000.0, MP3_TRACK_BILLION);
        appendMagnitude(&integerPart, 1000000, MP3_TRACK_MILLION);
        appendMagnitude(&integerPart, 1000, MP3_TRACK_THOUSAND);
        appendSubThousand((long)integerPart);
    }

    if (dp > 0) {
        appendElement(MP3_TRACK_POINT);
        for (uint8_t i=1; i<dp+1; i++) {
            uint8_t digit = (unsigned long)(fractionalPart*pow(10, i))%10;
            appendElement(MP3_TRACK_ZERO+digit);
        }
    }
}

bool DFPReader::reading()
{
    if (busy()) {
        return true;
    } else if (unplayedElements > 0) {
        return true;
    } else {
        return false;
    }
}

void DFPReader::resetReaderBuf()
{
    tailPtr = 0;
    unplayedElements = 0;
    if (busy()) {
        sendCmd(DFPlayerMini::Stop);
    }
}

uint8_t DFPReader::popElement()
{
    if (unplayedElements==0) {
        return 0;
    } else {
        uint8_t e = readerBuf[tailPtr];
        tailPtr = (tailPtr+1) % readerBufSize;
        unplayedElements--;
        return e;
    }   
}

bool DFPReader::appendElement(uint8_t value)
{
    DB(F("DFPReader::appendElement "));
    DBLN(value);
    if (unplayedElements >= readerBufSize) {   
        DBLN(F("DFPReader::appendElement ERROR: buffer full"));
        return false;
    } else {
        readerBuf[(tailPtr+unplayedElements)%readerBufSize] = value;
        unplayedElements++;
        return true;
    }
}

void DFPReader::appendSubThousand(int num)
{
    if (num >= 100) {
        appendElement(SMALL_NUMBERS[num / 100]);
        appendElement(MP3_TRACK_HUNDRED);
        num %= 100;
    }
    if (num >= 20) {
        appendElement(TENS[num / 10]);
        num %= 10;
    }
    if (num != 0) {
        appendElement(SMALL_NUMBERS[num]);
    }
}

void DFPReader::appendMagnitude(double* number, double magnitude, uint8_t magnitudeElement)
{
    if (*number < magnitude) {
        return;
    }

    appendSubThousand((int)(*number / magnitude));
    appendElement(magnitudeElement);
    *number = fmod(*number, magnitude);
}


