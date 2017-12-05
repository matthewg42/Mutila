#include <DFPlayerMini.h>
#include <SoftwareSerial.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t TxPin =       8;
const uint8_t RxPin =       9;
const uint8_t BusyPin =     10;
const uint16_t BetweenMs =  200;

SoftwareSerial SerialMP3(TxPin, RxPin);
DFPlayerMini mp3(SerialMP3, BusyPin);
uint32_t lastStop = 0;
bool playing = false;
int16_t count = 0;
int16_t track = 0;

void query() {
    DFPResponse r;
    r = mp3.query(DFPlayerMini::GetVolume);
    DB("Volume=");
    if (r.status == DFPResponse::Ok) { DB(r.arg); }
    else { DB("ERR"); }

    r = mp3.query(DFPlayerMini::GetStatus);
    DB(" Status=");
    if (r.status == DFPResponse::Ok) { DB(r.arg); }
    else { DB("ERR"); }

    r = mp3.query(DFPlayerMini::GetUSum);
    DB(" GetUSum=");
    if (r.status == DFPResponse::Ok) { DB(r.arg); }
    else { DB("ERR"); }

    r = mp3.query(DFPlayerMini::GetTfSum);
    DB(" GetTfSum=");
    if (r.status == DFPResponse::Ok) { DB(r.arg); count = r.arg; }
    else { DB("ERR"); }

    r = mp3.query(DFPlayerMini::GetUCurrent);
    DB(" GetUCurrent="); if (r.status == DFPResponse::Ok) { DB(r.arg); }
    else { DB("ERR"); }

    r = mp3.query(DFPlayerMini::GetUCurrent);
    DB(" GetTfCurrent=");
    if (r.status == DFPResponse::Ok) { DB(r.arg);  }
    else { DB("ERR"); }

    DBLN(' ');

}

void setup()
{
    Serial.begin(115200);
    SerialMP3.begin(9600);
    mp3.begin();

    // Let IO pins settle
    delay(200);  

    // Don't shout
    mp3.sendCmd(DFPlayerMini::SetVolume, 20);

    // Talk to the DFPlayer Mini device.  
    // Also sets the number of tracks.
    query();  
}

void playNext()
{
    DB("Playing track ");
    DBLN(track);
    playing = true;
    mp3.sendCmd(DFPlayerMini::PlayTf, track++);
    if (track > count) {
        track = 0;
    }
}

void loop() {
    uint32_t now = Millis();
    bool busy = mp3.busy();
    DB("busy: ");
    DBLN(busy);
    if (!busy) {
        if (playing) {
            DBLN("stopped");
            lastStop = now;
            playing = false;
        } 

        if (MillisSince(lastStop, now) > BetweenMs) {
            playNext();
        }
    } 
    // This is to reduce the jitter we have if we don't use the BUSY pin
    delay(100);
}

