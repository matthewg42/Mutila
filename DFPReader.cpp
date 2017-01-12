#include <MutilaDebug.h>
#include <DFPReader.h>

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

DFPReader::DFPReader(Stream& serial, uint8_t busyPin) :
    DFPlayerMini(serial, busyPin)
{
}

void DFPReader::begin()
{
    DFPlayerMini::begin();
    resetReaderBuf();
}

void DFPReader::update()
{
    DBLN(F("DFPReader::update"));
}

float mymodf(float number, float* ip)
{
   *ip = (long)number;
    return number - *ip;
}

void DFPReader::readNumber(float number, uint8_t dp)
{
    float ip, fp;

    if (dp == 0) {
        ip = round(number);
    } else {
        fp = mymodf(number, &ip);
    }
    
    readerBuf[0] = 0;

    if (ip == 0) {
        appendElement(MP3_TRACK_ZERO);
    } else {
        appendMagnitude(&ip, 1000000000000.0, MP3_TRACK_TRILLION);
        appendMagnitude(&ip, 1000000000.0, MP3_TRACK_BILLION);
        appendMagnitude(&ip, 1000000, MP3_TRACK_MILLION);
        appendMagnitude(&ip, 1000, MP3_TRACK_THOUSAND);
        appendSubThousand((int)ip);
    }

    if (dp > 0) {
        appendElement(MP3_TRACK_POINT);
        for (uint8_t i=0; i<dp; i++) {
            fp *= 10;
            if (i<dp-1) {
                appendElement(MP3_TRACK_ZERO+((int)fp)%10);
            }
        }
        fp = round(fp);
        appendElement(MP3_TRACK_ZERO+((int)fp)%10);
    }

    DB(F("Values for "));
    DB(number, dp);
    DB(F(" to "));
    DB(dp);
    DBLN(F(" d.p."));
    for (uint8_t i=0; i<headPtr; i++) {
        DBLN(readerBuf[i]);
    }
}

void DFPReader::resetReaderBuf()
{
    memset(readerBuf, 0, sizeof(uint8_t) * DFPR_SAY_BUF_SIZE);
    headPtr = 0;
    tailPtr = 0;
}

void DFPReader::appendElement(uint8_t value)
{
    // Remember, we're dealing with a ring buffer...
    if (headPtr < DFPR_SAY_BUF_SIZE) {
        readerBuf[headPtr++] = value;
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
    if (num != 0)
        appendElement(SMALL_NUMBERS[num]);
}

void DFPReader::appendMagnitude(float* number, float magnitude, uint8_t magnitudeElement)
{
    if (*number < magnitude)
        return;

    appendSubThousand((int)(*number / magnitude));
    appendElement(magnitudeElement);
    *number = fmod(*number, magnitude);
}


