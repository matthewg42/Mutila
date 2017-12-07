# Release Notes

## Version NEXT

Hot on the heels of the 1.1.0 release, this release is mainly because I'd broken the build for ESP projects be leaving a few straggler int variables unconverted to int16\_t. 

### Features:
- Added peek parameter to DebouncedButton::tapped (and pushed).
- Marked DebouncedButton::pushed as deprecated.
- Started writing this ChangeLog file.

### Bug fixes:
- Fixed broken ESP build caused by incomplete move to types from stdint.h.


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

