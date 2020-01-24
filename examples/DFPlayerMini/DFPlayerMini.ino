#include <DFPlayerMini.h>
#include <SoftwareSerial.h>
#include <Millis.h>
#include <MutilaDebug.h>

#if defined(ARDUINO_ESP8266_NODEMCU) 
const uint8_t TxPin =       D6;
const uint8_t RxPin =       D7;
const uint8_t BusyPin =     D5;
#else
const uint8_t TxPin =       6;
const uint8_t RxPin =       7;
const uint8_t BusyPin =     5;
#endif

// How long to wait between playing samples
const uint16_t BetweenMs =  1500;

// Volume from 1-30 (30 is loudest)
const uint16_t Volume =     15;

// This is based on the three example files from the audio directory
const int16_t TrackCount = 3;

// How often to print general status information
const uint16_t OutputPeriodMs = 1000;

// Global objects and variables
millis_t LastOutputMs = 0;
SoftwareSerial SerialMP3(TxPin, RxPin);
DFPlayerMini mp3(SerialMP3, BusyPin);
millis_t LastStop = 0;
bool Playing = false;
int16_t Track = 0;

// Function prototypes so we can put functions in any order and
// still build them with the Makefile.
void setup();
void loop();
void query();
void playNext();

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // Show we can handle Millis overflow
    AddMillisOffset(0xFFFFF000);

    // Show that we can handle Millis overflow
    SerialMP3.begin(9600);

    // Initialize the mp3 player object
    mp3.begin();

    // Set the volume
    mp3.sendCmd(DFPlayerMini::SetVolume, Volume);

    // Talk to the DFPlayer Mini device.  
    // Also sets the number of tracks.
    query();  

    Serial.println("setup() end");
}

void loop() {
    bool busy = mp3.busy();
    millis_t now = Millis();

    if (DoEvery(OutputPeriodMs, LastOutputMs)) {
        Serial.print("Millis=0x");
        Serial.print(Millis(), HEX);
        Serial.print(" busy pin=");
        Serial.println(busy);
    }

    if (!busy) {
        if (Playing) {
            Serial.println("State change to: stopped");
            LastStop = now;
            Playing = false;
        } 

        if (MillisSince(LastStop, now) > BetweenMs) {
            playNext();
        }
    } 
    // This is to reduce the jitter we have if we don't use the BUSY pin
    delay(100);
}

void query() {
    DFPResponse r;
    r = mp3.query(DFPlayerMini::GetVolume);
    Serial.print("Volume=");
    if (r.status == DFPResponse::Ok) { Serial.print(r.arg); }
    else { Serial.print("ERR"); }

    r = mp3.query(DFPlayerMini::GetStatus);
    Serial.print(" Status=");
    if (r.status == DFPResponse::Ok) { Serial.print(r.arg); }
    else { Serial.print("ERR"); }

    r = mp3.query(DFPlayerMini::GetUSum);
    Serial.print(" GetUSum=");
    if (r.status == DFPResponse::Ok) { Serial.print(r.arg); }
    else { Serial.print("ERR"); }

    r = mp3.query(DFPlayerMini::GetTfSum);
    Serial.print(" GetTfSum=");
    if (r.status == DFPResponse::Ok) { Serial.print(r.arg); }
    else { Serial.print("ERR"); }

    r = mp3.query(DFPlayerMini::GetUCurrent);
    Serial.print(" GetUCurrent="); if (r.status == DFPResponse::Ok) { Serial.print(r.arg); }
    else { Serial.print("ERR"); }

    r = mp3.query(DFPlayerMini::GetUCurrent);
    Serial.print(" GetTfCurrent=");
    if (r.status == DFPResponse::Ok) { Serial.print(r.arg);  }
    else { Serial.print("ERR"); }

    Serial.println();
}

void playNext()
{
    Serial.print("State change to: playing track ");
    Serial.println(Track);
    Playing = true;
    mp3.sendCmd(DFPlayerMini::PlayTf, Track++);
    if (Track > TrackCount) {
        Track = 0;
    }
}

