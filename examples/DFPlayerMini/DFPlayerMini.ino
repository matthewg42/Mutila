#include <DFPlayerMini.h>
#include <SoftwareSerial.h>
#include <Millis.h>
#include <MutilaDebug.h>

const uint8_t TxPin =       8;
const uint8_t RxPin =       9;
const uint8_t BusyPin =     10;
const uint16_t BetweenMs =  200;
const uint16_t Volume =     10;


SoftwareSerial SerialMP3(TxPin, RxPin);
DFPlayerMini mp3(SerialMP3, BusyPin);
uint32_t LastStop = 0;
bool Playing = false;
int16_t Count = 0;
int16_t Track = 0;

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
    if (r.status == DFPResponse::Ok) { Serial.print(r.arg); Count = r.arg; }
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
    Serial.println(F("\n\nS:setup"));
    SerialMP3.begin(9600);
    mp3.begin();

    // Let IO pins settle
    delay(200);  

    // Don't shout
    mp3.sendCmd(DFPlayerMini::SetVolume, Volume);

    // Talk to the DFPlayer Mini device.  
    // Also sets the number of tracks.
    query();  
    Serial.println(F("E:setup"));
}

void playNext()
{
    Serial.print("Playing track ");
    Serial.println(Track);
    Playing = true;
    mp3.sendCmd(DFPlayerMini::PlayTf, Track++);
    if (Track > Count) {
        Track = 0;
    }
}

void loop() {
    uint32_t now = Millis();
    bool busy = mp3.busy();
    Serial.print("busy: ");
    Serial.println(busy);
    if (!busy) {
        if (Playing) {
            Serial.println("stopped");
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

