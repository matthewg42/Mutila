#include <DFPlayerMini.h>
#include <SoftwareSerial.h>

SoftwareSerial SerialMP3(9, 8);
DFPlayerMini mp3(SerialMP3);

void doQuery(uint8_t cmd)
{
    DFPResponse r = mp3.query(cmd);
    Serial.print("doQuery(0x");
    Serial.print(cmd, HEX);
    if (r.status != DFPResponse::Ok) {
        Serial.println("): bad response");
    } else { 
        Serial.print("): msg=0x");
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
    doQuery(DFPlayerMini::GetStatus);
    delay(1000);
    doQuery(DFPlayerMini::GetVolume);
    delay(1000);
    doQuery(DFPlayerMini::GetUSum);
    delay(1000);
    doQuery(DFPlayerMini::GetTfSum);
    delay(1000);
    doQuery(DFPlayerMini::GetFlashSum);
    delay(1000);
    doQuery(DFPlayerMini::GetUCurrent);
    delay(1000);
    doQuery(DFPlayerMini::GetTfCurrent);
    delay(1000);
    doQuery(DFPlayerMini::GetFlashCurrent);
}

void loop()
{
    delay(1000);
    doQuery(DFPlayerMini::Next);
}
    
