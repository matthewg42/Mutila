#include <stdint.h>

#define PERSISTENTSETTINGCPP
#include "PersistentSetting.h"

uint16_t PersistentSettingOffset = 0;

PersistentString::PersistentString(uint8_t maxLength, String defaultValue, int32_t eepromOffset) : 
    _maxLength(maxLength),
    _eepromOffset(eepromOffset),
    _defaultValue(defaultValue)
{
    if (eepromOffset < 0) {
        _eepromOffset = PersistentSettingOffset;
    } else {
        _eepromOffset = eepromOffset;
    }
    PersistentSettingOffset = _eepromOffset + size();
    this->load();
}

/*! Reset the setting to its default value.
 *
 * \param saveIt if true, also save the setting to EEPROM.
 */
void PersistentString::reset(bool saveIt) 
{
    _value = _defaultValue;
    if (saveIt) {
        save();
    }
}

/*! Read the value from EEPROM - don't store it in the _value
 */
String PersistentString::savedValue() 
{
    String value = "";
#if defined(ESP8266) or defined(ESP32)
#warning ESP EEPROM functionality not yet implemented
#else
    // work out in which wear-levelling slot the last value was written
    for (uint16_t i=0; i<_maxLength; i++) {
        uint8_t c = EEPROM.read(_eepromOffset+i);
        if (c == 0) {
            break;
        }
        value += (char)c;
    }
#endif
    return value;
}

/*! Load value from EEPROM, and return it. If the value in EEPROM is not valid, use the default value.
 *
 * \return the loaded value.
 */
String PersistentString::load() 
{
    // work out in which wear-levelling slot the last value was written
    _value = savedValue();
    if (_value=="") {
        _value = _defaultValue;
    }
    return _value;
}

/*! Save the value to EEPROM
 *  Note: we're using the EEPROM.update() call, so EEPROM is only actually
 *  written if the value is different from the value currently in EEPROM. 
 *  This measure is an attempt to reduce wear on the EEPROM
 */
void PersistentString::save()
{
#if defined(ESP8266) or defined(ESP32)
#warning ESP EEPROM functionality not yet implemented
#else
    for (uint16_t i=0; i<_maxLength; i++) {
        EEPROM.update(_eepromOffset+i, i < _value.length() ? _value[i] : 0);
    }
#endif
}

/*! Get the current value of the setting
 */
String PersistentString::get() 
{ 
    return _value; 
}

/*! Get the default value of the setting
 */
String PersistentString::getDefault() 
{ 
    return _defaultValue; 
}

/*! Sets the in-RAM value of the setting.
 *  \param v the value to be set. If v is less than the minimum value or 
 *         greater than the maximum value, no change will be made.
 *  Note: this function does NOT save the new value to EEPROM. To do that, 
 *  save() must be called.
 */
String PersistentString::operator=(String v) 
{ 
    if (_maxLength < v.length()) {
        _value = v.substring(0,_maxLength);
    } else {
        _value = v;
    } 
    return _value; 
}

/*! Sets the in-RAM value of the setting.
 *  \param v the value to be set. If v is less than the minimum value or 
 *         greater than the maximum value, no change will be made.
 *  \return true if the value was set successfully, false otherwise (invalid v)
 *  Note: this function does NOT save the new value to EEPROM. To do that, 
 *  save() must be called.
 */
bool PersistentString::set(String v, bool saveIt) 
{ 
    *this = v; // use assignment operator so we truncate if needed
    if (saveIt) { 
        save();
    } 
    // not really necessary, but keeping SPI as similar to PersistentSetting as 
    // possible.
    return true; 
}

/*! Get the size in bytes of the setting in EEPROM.
 */
uint16_t PersistentString::size() 
{ 
    return _maxLength;
}

/*! Print values for this setting to serial (if DEBUG is enabled)
 */
void PersistentString::dump() 
{
    DB(F("off=0x"));
    DB(_eepromOffset, HEX);
    DB(F(" sz="));
    DB(size());
    DB(F(" val="));
    DBLN(_value);
}

