#include <SoftwareSerial.h>
#include <DFPlayerMini.h>
#include "TestBoardPins.h"

SoftwareSerial PlayerSerial(DfpmTxPin, DfpmRxPin);
DFPlayerMini Player(PlayerSerial, DfpmBusyPin);

