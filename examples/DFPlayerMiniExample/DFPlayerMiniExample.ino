#include <DFPlayerMini.h>
#include <SoftwareSerial.h>

SoftwareSerial SerialMP3(9, 8);
DFPlayerMini mp3(SerialMP3);

void setup()
{
    Serial.begin(115200);
    SerialMP3.begin(9600);
    delay(300);
}

void loop()
{
    int v = random(3,20);
    mp3.sendCmd(DFPlayerMini::SetVolume, v);
    mp3.sendCmd(DFPlayerMini::Next);
    DFPResponse r = mp3.fetch(DFPlayerMini::GetVolume);
    if (r.ok) {
        Serial.print("r.messageType=");
        Serial.print(r.messageType);
        Serial.print(" r.arg=");
        Serial.print(r.arg);
        Serial.print(" v=");
        Serial.println(v);
    } else {
        Serial.println("bad response");
    }

    delay(1000);
}
    
