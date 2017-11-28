#include <DFPReader.h>
#include <SoftwareSerial.h>
#include <MutilaDebug.h>

// DFP_TX_PIN describes the pin on the Arduino which has a connection
// to the TX pin on the DFPlayer Mini, and so on.
#define DFP_TX_PIN          5
#define DFP_RX_PIN          6
#define DFP_BUSY_PIN        10

SoftwareSerial SerialMP3(DFP_TX_PIN, DFP_RX_PIN);
DFPReader reader(SerialMP3, DFPlayerMini::PlayTf, DFP_BUSY_PIN);

void setup()
{
    Serial.begin(115200);

    // Make a softserial for the DFP comms
    SerialMP3.begin(9600); 
    reader.begin();

    // Let IO pins settle
    delay(200); 

    // don't shout
    reader.sendCmd(DFPlayerMini::SetVolume, 15); 
    reader.readNumber(-1, 0);
    reader.readNumber(3.1415926, 2);
    reader.readNumber(999.999, 2);

    DBLN("setup() complete");
}

void loop() {
    reader.update();
    delay(300);
}

