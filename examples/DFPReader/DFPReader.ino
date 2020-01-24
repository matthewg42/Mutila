#include <SoftwareSerial.h>
#include <DFPReader.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include "TestBoardPins.h"

// Volume from 1-30 (30 is loudest)
const uint16_t Volume = 15;

SoftwareSerial SerialMP3(DfpmTxPin, DfpmRxPin);
DFPReader reader(SerialMP3, DFPlayerMini::PlayTf, DfpmBusyPin);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    // Make a softserial for the DFP comms
    SerialMP3.begin(9600); 
    reader.begin();

    // Let IO pins settle
    delay(500); 

    // don't shout
    reader.sendCmd(DFPlayerMini::SetVolume, Volume); 
    reader.readNumber(-1, 0);           // expect "minus one"
    reader.readNumber(3.1415926, 2);    // expect "three point one four"
    reader.readNumber(999.999, 2);      // expect "one thousand point zero zero"

    Serial.println("setup() end");
}

void loop() {
    reader.update();
}

