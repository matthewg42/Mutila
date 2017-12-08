
# Mouse's Utilities for Arduino (Mutila)

Re-usable utility components for Arduino projects. All the stuff we all end up re-implementing every project - buttons, averaging samplers, voltage and current measurements calculations and so on. The classes and functions in this library are intended to be flexible, efficient and stable, as well as following a style which is broadly similar to the core Arduino libraries.

## Author & License

All code written by Matthew Gates (Mouse), and licensed under the GNU GPL version 3. See the LICENSE file for details.

## Feature Summary

### Inputs

A collection of classes and functions for nice handling of basic inputs (buttons and such). The classes are kept as simple as possible while having enough functionality to be useful. ''Time slice-based'' classes should have their ''update()'' method called as frequently as possible, which will return rapidly. These classes are an alternative to interrupt driven IO for projects where interrupts can't be used - e.g. where *Mutila* inputs must not interfere with timing of other parts of your project which might use interrupts themselves (e.g. motor control)

* *DigitalInputButton* - switch from a digital input pin.
* *AnalogInputButton* - switch from an analog input pin.
* *DualInputButton* - switch from combination of two other buttons.
* *DebouncedButton* - time slice-based debounced button class with input from a DigitalInputButton object.
* *DebouncedAnalogButton* - time slice-based debounced button class with input from an AnalogInputButton object.
* *DebouncedDualButton* - time slice-based debounced button class with input from a DualInputButton object.
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

* *BufferedSampler* - keeps a buffer of recent samples, providing ability to get average, minimum and maximum for values in the buffer.
* *EMASampler* - provides calculation of exponential moving average value for an analog input.

Sampling voltage and current values may be performed using the following classes, which are good examples of how to derive custom samplers from BufferedSampler and EMASampler:

* *BufferedVDivSampler* - measure voltage over a voltage divider using BufferedSampler.
* *EMAVDivSampler* - measure voltage over a voltage divider using EMASampler.
* *EMACurrentSampler* - measure current using an Allegro ACS756SCB-050B-PFF-T Bi-directional 50A hall effect sensor and EMASampler.

### DFPlayer Mini MP3 audio module

DFPlayer Mini is a neat and affordable audio module which can play MP3 files from an SD card with a serial interface for control. It can also drive a small speaker. Mutila provides the class *DFPlayerMini* for controlling such a device. *DFPReader* is a class which can be used to read out numbers and durations, using the samples in the *audio/* directory.

### HC-SR04 Ultrasonic Ranger

HC-SR04 ultrasonic range finding modules are inexpensive and popular modules used in Arduino projects. While using them is simple (it only takes a few lines of code to fetch and calculate the range), Mutila provides the following classes for clean usage of these modules, and enhanced functionality:

* *SonicRanger* - a basic wrapper around the code necessary to calculate the range of an object, done in the same style as other Mutila classes (with pins passes in a constructor and initialized in a begin() member).
* *EMASonicRanger* - periodic sampling of the range value, smoothed using the exponential moving average method.

### Heartbeat

Mutila's *Heartbeat* class can be used to blink and LED with variable patterns to give some diagnostic information about the state of the program without needed a more sophisticated display.

### Mode System

A *Mode* is a kind of sub-program which has distinct startup, shutdown and update routines.  For example, your program might have a special setup mode which suspends normal operations while settings are altered. The *ModeManager* class can be used to switch between such mutually exclusive modes while keeping your main loop clean and simple. 

Modes may be arranged in a hierarchical manner using the *ParentMode* class. This can be useful when building hierarchical menu systems which a couple of buttons.

## API Documentation

Doxygen-generated documentation can be found here: https://matthewg42.github.io/Mutila/

### Generating documentation

1.  Install Doxygen
2.  Run ''doxygen'' from the root of this project - html is generated in doc/html

## Ideas for future development

### Templatised PersistentSetting classes

Similar to the ones implemented in EspApConfigurator (by the same Author), but that works with both ESP and Arduino hardware (the use of the EEPROM library for ESP devices is incompatible with regular Arduino EEPROM usage).

This should include the same first-byte-of-eeprom-is-fingerprint thing, which lets is auto-revert to defaults if the settings fingerprint doesn't match what's in EEPROM (e.g. first time we burn the firmware to a device).

### Auto version message

It would be really nice to have some mechanism to write the current project version, and library versions into flash automatically.  By version I guess I mean git short hash of library version from library.properties.

### StickyButton

* When pushed, stays on for some period of time and then switches off.
* Pushing when on restarts the on timer.

### n-state button

* state=0 --> state=1 ... --> state=n-1 --> state=0.
* This makes ToggleButton just an n-state where n=2.

### DFPlayerMini

* doc ops which create reply
* asynchronous commands (i.e. do not wait for serial, use update() to send bytes one at a time)

## Development Workflow

At time of writing, Mutila is a one-Mouse project. versions up until v1.1.0 were not made into releases, and most work was done directly in master. However, enough projects now use Mutila that is makes sense to start being a bit more structured, so here's how it's going to work from now (until I need to change it again).

* After v1.1.1, the *master* branch is just for releases, which (I hope) will be well-tested and stable.
* Each release will be summarised in the ReleaseNotes.md file.
* Minor new features, bug fixes and the like will go in the *dev* branch, which will periodically be merged with master to create a new release.
* Major new features will be created in feature branches.

