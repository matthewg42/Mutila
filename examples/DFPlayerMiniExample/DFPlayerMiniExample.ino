#include <DFPlayerMini.h>
#include <SoftwareSerial.h>

SoftwareSerial SerialMP3(9, 8);
DFPlayerMini mp3(SerialMP3);

void setup()
{
    SerialMP3.begin(9600);
    mp3.setVolume(15);
    delay(500);
    mp3.play(10);
}

void loop()
{
}
