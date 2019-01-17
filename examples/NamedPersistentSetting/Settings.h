#pragma once

#include <PersistentSetting.h>

extern NamedPersistentSetting<bool> BoolSetting;
extern NamedPersistentSetting<uint32_t> UInt32Setting;
extern NamedPersistentSetting<int16_t> Int16Setting;
extern NamedPersistentSetting<double> DoubleSetting;
extern NamedPersistentSetting<float> FloatSetting;

// The first time the device is booted with this firmware, we see if MagicSetting
// is set to MagicNumber. If it is, we deduce that this device has already been
// set up with these settings and does not need the defaults set.
extern PersistentSetting<uint16_t> MagicSetting;
const uint16_t MagicNumber = 0xADDA;  // do not set this to 0.
