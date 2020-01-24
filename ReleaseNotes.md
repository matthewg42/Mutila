# Release Notes

## Version 1.3.0

### Changed
- Pins for examples have changed on the Arduino Nano build (buttons now on pins 2 & 3 for future features with interrupts). See `examples/README.md` for new pin layout.
- All places where millis are used have now been converted to typedef `millis_t`, defined in `Millis.h`. `micros_t` typedef also added.
- Sampler classes take a millis_t sample period instead of uint16_t as preventative for [unlikely] integer overflow. Uses slightly more RAM.

### Removed
- Remove long-deprecated DualButton class.

### Other
- Tweak docs & examples to remove typos / inconsistencies.
- Makefile build of examples no longer suppresses some warnings it used to (no longer a problem)

## Version 1.2.0

### Features
- PersistentSetting class now supports a wear-levelling scheme.

## Version 1.1.7

### Bug fixes:
- Fix incorrect logic for sticky option of MultiThrowSwitch.

## Version 1.1.6

### Features
- MultiThrowSwitch class added.

### Bug fixes:
- Add virtual destrubtor to DebounedButton to it may be derived from in user code.

## Version 1.1.5

### Features
- QuantizedPot class added.

### Bug fixes:

## Version 1.1.4

### Features
- NamedPersistentSetting template class in case you wish to attach a string identifier to your PersistenSettings.
- Accessor functions for PersistenSettings minimum, maximum and default values.

### Bug fixes:
- PersistentSettings.save saveIt parameter now functions we desired.

## Version 1.1.3

### Features
- PersistentSetting template class for EEPROM-backed settings for numeric and bool types.
- CommandInterface base class for implementing simple CLIs.

## Version 1.1.2

### Features:
- FreeRam() function provides platform-independent interface to getting free memory.

### Other:
- Cosmetic and documentation improvements.
- Better library.json for PlatformIO.
- New example `DFPCommander`: command line control and testing of DF Player Mini module.

## Version 1.1.1

Bug fix release.

### Features:
- Added peek parameter to AbstractDebouncedButton::tapped and AbstractDebouncedButton::pushed. Default set for backwards compatibility.
- Added bootWait parameter DFPlayerMini::begin() and DFPReader::begin(). Default set for backwards compatibility.
- Added ESP Makefiles for all examples.
- Added ESP build conditionals for all examples, and documented ESP-based test setup.

### Bug fixes:
- Fixed broken ESP build caused by incomplete move to types from stdint.h.
- Fix broken build of DFPReader on ESP8266 (work-around ESP8266 library fmod bug).

### Other
- Much cleanup and improvements in consistency of example code.
- Arduino 1.5 library compatibility.

## Version 1.1.0

This release is primarily to address the *Millis wrap problem*, but I ended up bundling some other changes in there too.  A few classes have changed, which could potentially break compatibility with existing sketches, but only for classes which are probably only used internally, like RawButton which doesn't make a lot of sense to use in an end-user sketch.

### Features
- Implement MillisSince and DoEvery in Millis.h to address Millis wrap problem.
- Use new functions throughout Mutila code and examples.
- Improved documentation.
- Move to using stdint.h types rather than simple int and friends, for more consistent behaviour across platforms.
- New ModeManager class and example.
- Changed a lot of #defined globals into static const variables in appropriate classes to clean up the global name-space; removed Mutila.h.
- Created and documented standard test rig using a Nano, DFPlayer Mini, potential divider, two buttons and a sonic ranger module.
- Rearranged button hierarchy. New AbstractButton and AbstractDebouncedButton classes help reduce duplicated code. Three basic immediate button types (which don't need a time slice):
    - Renamed RawButton to DigitalInputButton.
    - Created Analog ButtonInputButton.
    - DualInputButton, which can be any combination of DigitalInputButton and ButtonInputButton, and can work in Or, Xor and And modes.

### Bug fixes
- Heartbeat::Mode On mode now doesn't continuously switch LED on and off every update().
- Fix Mode::update() with interval set calling too many times immediately after Mode startup.

