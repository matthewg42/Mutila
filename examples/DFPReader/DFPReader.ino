#include <SoftwareSerial.h>
#include <DFPReader.h>
#include <MutilaDebug.h>
#include <Millis.h>

// TxPin describes the pin on the Arduino which has a connection
// to the TX pin on the DFPlayer Mini, and so on.
#if defined(ARDUINO_ESP8266_NODEMCU) 
const uint8_t TxPin =       D6;
const uint8_t RxPin =       D7;
const uint8_t BusyPin =     D5;
#else
const uint8_t TxPin = 8;
const uint8_t RxPin = 9;
const uint8_t BusyPin = 10;
#endif

// Volume from 1-30 (30 is loudest)
const uint16_t Volume =     15;

SoftwareSerial SerialMP3(TxPin, RxPin);
DFPReader reader(SerialMP3, DFPlayerMini::PlayTf, BusyPin);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show we can handle Millis overflow
    addMillisOffset(0xFFFFF000);

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

