#pragma once

#include <PersistentSetting.h>

extern PersistentSetting<bool> BoolSetting;
extern PersistentSetting<uint32_t> UInt32Setting;
extern PersistentSetting<int16_t> Int16Setting;
extern PersistentSetting<double> DoubleSetting;
extern PersistentSetting<float> FloatSetting;

// The first time the device is booted with this firmware, we see if MagicSetting
// is set to MagicNumber. If it is, we deduce that this device has already been
// set up with these settings and does not need the defaults set.
extern PersistentSetting<uint16_t> MagicSetting;
const uint16_t MagicNumber = 0xABBA;  // do not set this to 0.

