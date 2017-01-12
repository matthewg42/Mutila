#include <DFPlayerMini.h>
#include <SoftwareSerial.h>
#include <MutilaDebug.h>

#define BUSY_PIN        10
#define DFTX_PIN        5 
#define DFRX_PIN        6 
#define BETWEEN_MS      200

SoftwareSerial SerialMP3(DFTX_PIN, DFRX_PIN);
DFPlayerMini mp3(SerialMP3, BUSY_PIN);
unsigned long lastStop = 0;
bool playing = false;
int count = 0;
int track = 0;

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
    if (r.status == DFPResponse::Ok) { Serial.print(r.arg); count = r.arg; }
    else { Serial.print("ERR"); }

    r = mp3.query(DFPlayerMini::GetUCurrent);
    Serial.print(" GetUCurrent="); if (r.status == DFPResponse::Ok) { Serial.print(r.arg); }
    else { Serial.print("ERR"); }

    r = mp3.query(DFPlayerMini::GetUCurrent);
    Serial.print(" GetTfCurrent=");
    if (r.status == DFPResponse::Ok) { Serial.print(r.arg);  }
    else { Serial.print("ERR"); }

    Serial.println(' ');

}

void setup()
{
    Serial.begin(115200);
    SerialMP3.begin(9600);
    mp3.begin();

    // Let IO pins settle
    delay(200);  

    // Don't shout
    mp3.sendCmd(DFPlayerMini::SetVolume, 15);

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
    unsigned long now = millis();
    bool busy = mp3.busy();
    DB("busy: ");
    DBLN(busy);
    if (!busy) {
        if (playing) {
            DBLN("stopped");
            lastStop = now;
            playing = false;
        } 

        if (now > lastStop + BETWEEN_MS) {
            playNext();
        }
    } 
    // This is to reduce the jitter we have if we don't use the BUSY pin
    delay(100);
}

