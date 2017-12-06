#include "MutilaDebug.h"
#include "DFPReader.h"
#include "Millis.h"

const uint8_t DFPReader::SMALL_NUMBERS[] = {
        Mp3TrackZero, Mp3TrackZero+1, Mp3TrackZero+2, Mp3TrackZero+3, 
        Mp3TrackZero+4, Mp3TrackZero+5, Mp3TrackZero+6, Mp3TrackZero+7, 
        Mp3TrackZero+8, Mp3TrackZero+9, Mp3TrackZero+10, Mp3TrackZero+11, 
        Mp3TrackZero+12, Mp3TrackZero+13, Mp3TrackZero+14, Mp3TrackZero+15,
        Mp3TrackZero+16, Mp3TrackZero+17, Mp3TrackZero+18, Mp3TrackZero+19
};

const uint8_t DFPReader::TENS[] = {
        0, 0, Mp3TrackTwenty, Mp3TrackThirty, Mp3TrackFourty,
        Mp3TrackFifty, Mp3TrackSixty, Mp3TrackSeventy, 
        Mp3TrackEighty, Mp3TrackNinety
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
        if (MillisSince(lastPlayStart) >= PlaybackStartMs) {
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
    lastPlayStart = Millis();
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
        appendElement(Mp3TrackMinus);
        integerPart = fabs(integerPart);
    }

    if (integerPart < 0.1) {
        appendElement(Mp3TrackZero);
    } else {
        appendMagnitude(&integerPart, 1000000000000.0, Mp3TrackTrillion);
        appendMagnitude(&integerPart, 1000000000.0, Mp3TrackBillion);
        appendMagnitude(&integerPart, 1000000, Mp3TrackMillion);
        appendMagnitude(&integerPart, 1000, Mp3TrackThousand);
        appendSubThousand((long)integerPart);
    }

    if (dp > 0) {
        appendElement(Mp3TrackPoint);
        for (uint8_t i=1; i<dp+1; i++) {
            uint8_t digit = (uint32_t)(fractionalPart*pow(10, i))%10;
            appendElement(Mp3TrackZero+digit);
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

void DFPReader::appendSubThousand(int16_t num)
{
    if (num >= 100) {
        appendElement(SMALL_NUMBERS[num / 100]);
        appendElement(Mp3TrackHundred);
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


