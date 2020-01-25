# Mutila Examples

There's an example for classes in the Mutila library. They all print output to Serial at 115200 baud.

## Hardware

Some of the examples require extra hardware with the following configurations for a test rig (Mutila is tested with an Arduino Nano and a NodeMCU 0.9 (Amica form factor), as these boards are very often used in the author's projects).

### Test Rig for Arduino Nano

- Arduino Nano 328P
    - Push to make button GND -> Button -> pin 3 (primary button used when only one button is used)
    - Push to make button GND -> Button -> pin 2 (secondary button)
    - Push to make button GND -> Button -> pin 4 (tertiary button)
    - 10 KOhm linear potential divider with centre pin -> A5, outer pins GND & 5V
    - DFPlayer Mini:
        - DFPlayer Mini pin RX -> 1 KOhm resistor -> Arduino 7
        - DFPlayer Mini pin TX -> 1 KOhm resistor -> Arduino 6
        - DFPlayer Mini pin BUSY -> Arduino 5
        - DFPlayer Mini pin VCC -> Arduino 5V
        - DFPlayer Mini pin GND -> Arduino Gnd
        - DFPlayer Mini pin SPK_1 -> 8 Ohm, 0.2 Watt speaker
        - DFPlayer Mini pin SPK_2 -> 8 Ohm, 0.2 Watt speaker
        - Micro SD card formatted with VFAT, with files from Mutila's *audio* directory copied into the mp3 directory of the card
    - HC-SR04 sonic ranger module:
        - HC-SR04 pin Gnd -> Arduino Gnd
        - HC-SR04 pin Vcc -> Arduino 5V
        - HC-SR04 pin Echo -> Arduino 8
        - HC-SR04 pin Trig -> Arduino 9

### Test Rig for NodeMCU (ESP8266)

- NodeMCU Amica (version 0.9, ESP-12 Module)
    - Push to make button GND -> Button -> pin D1 (primary button used when only one button is used)
    - Push to make button GND -> Button -> pin D2 (secondary button)
    - 10 KOhm linear potential divider with centre pin -> A0, outer pins GND & 5V
    - DFPlayer Mini:
        - DFPlayer Mini pin RX -> Arduino D7
        - DFPlayer Mini pin TX -> 1 KOhm resistor -> Arduino D6
        - DFPlayer Mini pin BUSY -> Arduino D5
        - DFPlayer Mini pin VCC -> Arduino 5V
        - DFPlayer Mini pin GND -> Arduino Gnd
        - DFPlayer Mini pin SPK_1 -> 8 Ohm, 0.2 Watt speaker
        - DFPlayer Mini pin SPK_2 -> 8 Ohm, 0.2 Watt speaker
        - Micro SD card formatted with VFAT, with files from Mutila's *audio* directory copied into the mp3 directory of the card
    - HC-SR04 sonic ranger module:
        - HC-SR04 pin Gnd -> Arduino Gnd
        - HC-SR04 pin Vcc -> Arduino 5V
        - HC-SR04 pin Echo -> Arduino D0
        - HC-SR04 pin Trig -> Arduino D3

Because the NodeMCU has limited pins, you might need to plug/unplug things in different examples.

## Building

All examples may be built with the Arduino IDE by opening the .ino file, selecting the appropriate target hardware and clicking the Verify toolbar button.

### Using make

Using make can be faster and offers more flexible work-flows than using the Arduino IDE, and may be preferable for some. All the examples come with two makefiles - one for Arduino targets, and the other for ESP targets.

#### Arduino

You can use [the Arduino Makefile](https://github.com/sudar/Arduino-Makefile) as follows (this process has only tested on a Fedora Linux system):

1. Install the Arduino IDE as normal.
2. Clone the [Git repository](https://github.com/sudar/Arduino-Makefile.git) somewhere, for example /home/bob/Arduino-Makefile/. 
3. Set the environment variable ARDUINO\_DIR to the path where you installed the Arduino IDE.
4. Set the environment variable ARDUINO\_MAKEFILE to the full path of the Arduino.mk file in the Arduino Makefile repository.

For example, if you installed the IDE to /opt/arduino-1.8.5/, and the Arduino Makefile in /home/bob/Arduino-Makefile/, you would set up your environment with the following commands:

```bash
export ARDUINO_DIR=/opt/arduino-1.8.5
export ARDUINO_MAKEFILE=/home/bob/Arduino-Makefile/Arduino.mk
```

To build an example, change into the directory for an example, and edit the Makefile - ensure the BOARD\_TAG and BOARD\_SUB values are set for your hardware (a few examples can be found in comment form in each example Makefile), then save the Makefile and build by entering the command "make". You can upload to a connected arduino using "make upload", and get other options with "make help".

Once you've verified that the environment variables are set up properly, you might want to add the export commands to you $HOME/.profile.

#### ESP8266 and ESP32

You can use [the makeEspArduino](https://github.com/plerup/makeEspArduino) as follows (this process has only tested on a Fedora Linux system):

1. Install the Arduino IDE as normal.
2. Clone the [Git repository](https://github.com/plerup/makeEspArduino.git) somewhere, for example /home/bob/makeEspArduino/.
3. Set the environment variable ARDUINO\_DIR to the path where you installed the Arduino IDE.
4. Set the environment variable ESP\_MAKEFILE to the full path of the makeEspArduino.mk file in the makeEspArduino repository.

For example, if you installed the IDE to /opt/arduino-1.8.5/, and the Arduino Makefile in /home/bob/makeEspArduino/, you would set up your environment with the following commands:

```bash
export ARDUINO_DIR=/opt/arduino-1.8.5
export ESP_MAKEFILE=/home/bob/makeEspArduino/makeEspArduino.mk
```

To build an example, change into the directory for an example, and edit the Makefile.esp - ensure the BOARD value is set for your hardware (a few examples can be found in comment form in each example Makefile.esp), then save the Makefile and build by entering the command "make -f Makefile.esp". You can upload to a connected arduino using "make -f Makefile.esp upload", and get other options with "make -f Makefile.esp help".

Once you've verified that the environment variables are set up properly, you might want to add the export commands to you $HOME/.profile.

NOTE: the makefile for NodeMCU is not functioning correctly at time of writing (2020-01-20).

