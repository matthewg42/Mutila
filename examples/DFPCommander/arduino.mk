# Either define ARDUINO_MAKEFILE in the environment to be the full path 
# to where you have Arduino.mk installed, or just edit it here...

# This is a dependency of Mutila 
ARDUINO_LIBS += Adafruit_NeoPixel

ifndef ARDUINO_MAKEFILE
	ARDUINO_MAKEFILE := /opt/Arduino-Makefile/Arduino.mk
endif

include $(ARDUINO_MAKEFILE)


