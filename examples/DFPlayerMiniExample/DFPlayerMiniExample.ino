#include <DFPlayerMini.h>
#include <SoftwareSerial.h>

SoftwareSerial SerialMP3(9, 8);
DFPlayerMini mp3(SerialMP3);

void query(uint8_t cmd)
{
    DFPResponse r = mp3.fetch(cmd);
    Serial.print("query=");
    Serial.print(cmd);
    if (!r.ok) {
        Serial.println(": bad response");
    } else { 
        Serial.print(": msg=0x");
        Serial.print(r.messageType, HEX);
        Serial.print(" arg=");
        Serial.println(r.arg);
    }
    delay(500);

}

void setup()
{
    Serial.begin(115200);
    SerialMP3.begin(9600);
    delay(300);
    query(DFPlayerMini::GetStatus);
    delay(1000);
    query(DFPlayerMini::GetVolume);
    delay(1000);
    query(DFPlayerMini::GetUSum);
    delay(1000);
    query(DFPlayerMini::GetTfSum);
    delay(1000);
    query(DFPlayerMini::GetFlashSum);
    delay(1000);
    query(DFPlayerMini::GetUCurrent);
    delay(1000);
    query(DFPlayerMini::GetTfCurrent);
    delay(1000);
    query(DFPlayerMini::GetFlashCurrent);
}

void loop()
{
    delay(1000);
    query(DFPlayerMini::Next);
}
    
