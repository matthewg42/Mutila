
# Mouse's Utilities for Arduino (Mutila)

## Summary

Re-usable utility components for Arduino projects. All the stuff we all end up re-implementing every project - buttons, averaging samplers, voltage and current measurements calculations and so on.

### Inputs

A collection of classes and functions for nice handling of basic inputs (buttons and such). The classes are kept as simple as possible while having enough functionality to be useful. ''Timeslice-based'' classes should have their ''update()'' method called as frequently as possible, which will return rapidly. These classes are an alternative to interrupt driven IO for projects where interrupts can't be used - e.g. where *Mutila* inputs must not intefere with timing of other parts of your project which might use interrupts themselves (e.g. motor control)

* *RawButton* - switch with optional logic inversion (pullup).
* *DebouncedButton* - timeslice-based debounced push button class.
* *DualButton* - works like a DebouncedButton which has two inputs (from separate DebouncedButtons). The purpose of this class is to enable easy addition of a second control (e.g. from radio remote control) to a system with an existing DebouncedButton, without having to change/clutter up your firmware logic.
* *DiscretePot* - use a potential divider attached to an analog input to return a discrete value within a specified range - includes smoothing.
* *ToggleButton* - each press flips state from on to off.

Terms used for Mutila input classes:

* *on*: instantaneous logical value.
* *pushed*: button is on now, and this is the first time pushed has been tested since the button became on.
* *tapped*: button has been pushed and released.
* *held*: is on and has been for more than some period of time (over and above debouncing).
* *repeat*: is held, but will only return true periodically - the delay between true returns is different (typically longer) for the first repeat, and then shorter for subsequent repeats. This follows common repeat characteristics of computer keyboards.

### Samplers

Samplers read from analog input pins and allow some operations to be performed on the data - typically calculating some sort of average value for the pin to help de-noise signals from sensors.

* *BufferedSampler* - keeps a buffer of recent samples, providing ability to get average, minimum and maximum for values in the buffer
* *EMASampler* - provides calculation of exponential moving average value for an analog input

Sampling voltage and current values may be performed using the following classes, which are good examples of how to derive custom samplers from BufferedSampler and EMASampler:

* *BufferedVDivSampler* - measure voltage over a voltage divider using BufferedSampler.
* *EMAVDivSampler* - measure voltage over a voltage divider using EMASampler.
* *EMACurrentSampler* - measure current using an Allegro ACS756SCB-050B-PFF-T Bi-directional 50A hall effect sensor and EMASampler.

Current measuement may be achieved using an Allegro ACS756SCB-050B-PFF-T Bi-directional 50A hall effect sensor and the class

### DFPlayer Mini MP3 audio module

DFPlayer Mini is a neat and affordable audio module which can play MP3 files from an SD card, with a serial interface for control. It can also drive a small speaker. Mutila provides the class *DFPlayerMini* for controlling such a device. *DFPReader* is a class which can be used to read out numbers and durations, using the samples in the *audio/* directory.

### HC-SR04 Ultrasonic Ranger

HC-SR04 ultrasonic range finding modules are inexpensive and popular modules used in Arduino projects. While using them is simple (it only takes a few lines of code to fetch and calculate the range), Mutila provides the following classes for clean usage of these modules, and enhanced functionality:

* *SonicRanger* - a basic wrapper around the code necessary to calculate the range of an object, done in the same style as other Mutila classes (with pins passes in a constructor and initialized in a begin() member).
* *EMASonicRanger* - periodic sampling of the range value, smoothed using the exponential moving average method.

## Author & License

All code written by Mouse <mouse@orthogonal-systems.co.uk>, and licensed under the GNU GPL v3. See the LICENSE file for details.

## API Documentation

Doxygen-generated documentation can be found on the Orthogonal Systems website at http://orthogonal-systems.co.uk/doc/mutila/

### Generating documentation

1.  Install Doxygen
2.  Run ''doxygen'' from the root of this project - html is generated in doc/html

## Ideas for future development

### DebouncedButton

* DebouncedButton::wasPressed() should return number of presses if more than one since last test.

### StickyButton

* When pushed, stays on for some period of time and thn switches off.
* Pushing when on restarts the on timer.

### n-state button

* state=0 --> state=1 ... --> state=n-1 --> state=0.
* This makes ToggleButton just an n-state where n=2.

### DFPlayerMini

* add busy detection / wait function
* doc ops which create reply
* asynchronous commands (i.e. do not wait for serial, use update() to send bytes one at a time)

