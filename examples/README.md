Some of the examples require extra hardware.  Here is the test setup which was used when these examples were developed:

- Arduino Nano 328P
    - Push to make button GND -> Button -> pin D6 (primary button used when only one button is used)
    - Push to make button GND -> Button -> pin D5 (secondary button)
    - 10 KOhm linear potential divider with centre pin -> A0, outer pins GND & 5V
    - DFPlayer Mini:
        - DFPlayer Mini pin RX -> 1 KOhm resistor -> Arduino D8
        - DFPlayer Mini pin TX -> 1 KOhm resistor -> Arduino D9
        - DFPlayer Mini pin BUSY -> Arduino D10
        - DFPlayer Mini pin VCC -> Arduino 5V
        - DFPlayer Mini pin GND -> Arduino Gnd
        - DFPlayer Mini pin SPK_1 -> 8 Ohm, 0.2 Watt speaker
        - DFPlayer Mini pin SPK_2 -> 8 Ohm, 0.2 Watt speaker
        - Micro SD card formatted with VFAT, with files from Mutila's *audio* directory copied into the mp3 directory of the card
    - HC-SR04 sonic ranger module:
        - HC-SR04 pin Gnd -> Arduino Gnd
        - HC-SR04 pin Vcc -> Arduino 5V
        - HC-SR04 pin Echo -> Arduino D4
        - HC-SR04 pin Trig -> Arduino D3

