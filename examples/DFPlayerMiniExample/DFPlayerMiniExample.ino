#include <DFPlayerMini.h>
#include <SoftwareSerial.h>

SoftwareSerial SerialMP3(9, 8);
DFPlayerMini mp3(SerialMP3);
int count = 0;

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
    Serial.print(" GetUCurrent=");
    if (r.status == DFPResponse::Ok) { Serial.print(r.arg); }
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
    delay(300);  // settle serial
    mp3.sendCmd(DFPlayerMini::SetVolume, 15); // don't shout
    query();
}

void loop() {

    for (int i=0; i<1; i++) {
        int t = random(count);
        Serial.print("Playing track: ");
        Serial.println(t);
        mp3.sendCmd(DFPlayerMini::Play, t);
        delay(1200);
    }
    query();
    delay(4000);
}

