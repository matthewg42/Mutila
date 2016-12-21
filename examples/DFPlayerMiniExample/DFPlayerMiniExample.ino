#include <DFPlayerMini.h>
#include <SoftwareSerial.h>

SoftwareSerial SerialMP3(9, 8);
DFPlayerMini mp3(SerialMP3);

void query() {
    DFPResponse r;
    r = mp3.query(DFPlayerMini::GetVolume);
    Serial.print("Volume=");
    Serial.print(r.arg);

    r = mp3.query(DFPlayerMini::GetStatus);
    Serial.print(" Status=");
    Serial.print(r.arg);

    r = mp3.query(DFPlayerMini::GetUSum);
    Serial.print(" GetUSum=");
    Serial.print(r.arg);

    r = mp3.query(DFPlayerMini::GetTfSum);
    Serial.print(" GetTfSum=");
    Serial.print(r.arg);

    r = mp3.query(DFPlayerMini::GetUCurrent);
    Serial.print(" GetUCurrent=");
    Serial.print(r.arg);

    r = mp3.query(DFPlayerMini::GetUCurrent);
    Serial.print(" GetTfCurrent=");
    Serial.println(r.arg);

}

void setup()
{
    Serial.begin(115200);
    SerialMP3.begin(9600);
    delay(300);  // settle serial
    mp3.sendCmd(DFPlayerMini::SetVolume, 15); // don't shout

}

void loop() {
    query();

    delay(100);
    // Play the first few samples on the card
    mp3.query(DFPlayerMini::Play, 4);
    delay(1000);
    mp3.sendCmd(DFPlayerMini::Next);
    delay(1000);
    mp3.sendCmd(DFPlayerMini::Next);
    delay(2000);

    // Test Prev cmd wrapping...
    mp3.sendCmd(DFPlayerMini::Prev);
    delay(1000);
    mp3.sendCmd(DFPlayerMini::Prev);
    delay(1000);
    mp3.sendCmd(DFPlayerMini::Prev);
    delay(1000);
    mp3.sendCmd(DFPlayerMini::Prev);
    delay(4000);
}

