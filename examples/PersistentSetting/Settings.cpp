#include "Settings.h"

// Make sure the EEPROM offset is such that the settings do not overlap, else
// saving one value could corrupt another.
//
// On Arduino Nano:
// sizeof char:       1
// sizeof short:      2
// sizeof int:        2
// sizeof long:       4
// sizeof long long:  8
// sizeof float:      4
// sizeof double:     4
//
//                                                  Min     Max         Default         Wear
//                                                  value   value       value           level
PersistentSetting<bool> BoolSetting             (   false,  true,       true,           3);
PersistentSetting<uint32_t> UInt32Setting       (   1000,   100000,     2000,           2);
PersistentSetting<int16_t> Int16Setting         (   50,     1000,       777             );
PersistentSetting<double> DoubleSetting         (   -10e4,  10e4,       3.14159265359   );
PersistentSetting<float> FloatSetting           (   -1,     1,          0.66666666666   );

// Named settings                                   Min     Max         Default         Name                Wear
//                                                  value   value       value                               Level
NamedPersistentSetting<bool> NamedBoolSetting   (   false,  true,       false,          "Truth is True"      );
NamedPersistentSetting<float> NamedFloatSetting (   0,      10e10,      6.28318530718,  "Better than Pi",   4);

// Magic value
PersistentSetting<uint16_t> MagicSetting        (   0,      UINT16_MAX, MagicNumber);

