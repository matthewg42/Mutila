#include <Arduino.h>
#include <SoftwareSerial.h>
#include <MutilaDebug.h>
#include <DFPlayerMini.h>
#include <Millis.h>
#include "Config.h"
#include "DFPlayerCLI.h"
#include "Player.h"

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    DFPlayerCLI.begin(Serial);
    PlayerSerial.begin(9600);
    Player.begin();
    Player.sendCmd(DFPlayerMini::SetVolume, InitialVolume);
}

void loop()
{
    DFPlayerCLI.update();
}

