#include <SoftwareSerial.h>
#include <DFPlayerMini.h>
#include <DFPReader.h>
#include <MutilaDebug.h>
#include <DebouncedButton.h>
#include <Millis.h>
#include "TestBoardPins.h"

// Volume from 1-30 (30 is loudest)
const uint16_t Volume = 15;

typedef struct {
    double value;
    uint8_t dp;
    const char* desc;
} read_info_t;

read_info_t read_info[3];
uint8_t read_idx = 0;
DebouncedButton Button1(Button1Pin);
DebouncedButton Button2(Button2Pin);
SoftwareSerial SerialMP3(DfpmTxPin, DfpmRxPin);
DFPReader reader(SerialMP3, DFPlayerMini::PlayTf, DfpmBusyPin);

void addStuffToRead()
{
    Serial.print(F("reading: "));
    Serial.println(read_info[read_idx].desc);
    reader.readNumber(read_info[read_idx].value, read_info[read_idx].dp);
    read_idx = ( read_idx + 1 ) % 3;
}

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    // Make a softserial for the DFP comms
    SerialMP3.begin(9600); 
    reader.begin();
    Button1.begin();
    Button2.begin();

    read_info[0].value = -1;
    read_info[0].dp = 0;
    read_info[0].desc = "minus one";
    read_info[1].value = 3.1415926;
    read_info[1].dp = 2;
    read_info[1].desc = "three point one four";
    read_info[2].value = 999.999;
    read_info[2].dp = 2;
    read_info[2].desc = "one thousand point zero zero";

    // Let DFPlayerMini boot
    delay(500); 

    // Over-ride the delay between sending
    reader.ResponseTimeoutMs = 5;

    // don't shout
    reader.sendCmd(DFPlayerMini::SetVolume, Volume); 

    addStuffToRead();

    Serial.println("setup() end");
}

void loop() {
    reader.update();
    Button1.update();
    Button2.update();

    if (Button1.pushed()) {
        addStuffToRead();
    }

    if (Button2.pushed()) {
        reader.resetReaderBuf();
    }
}

