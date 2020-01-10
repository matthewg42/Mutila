#include <SoftwareSerial.h>
#include <DFPlayerMini.h>
#include "Config.h"

SoftwareSerial PlayerSerial(TxPin, RxPin);
DFPlayerMini Player(PlayerSerial, BusyPin);

