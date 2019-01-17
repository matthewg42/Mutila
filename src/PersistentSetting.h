#pragma once

#include <Arduino.h>
#include <MutilaDebug.h>
#include <stdint.h>
#include <EEPROM.h>

// defined in PersistentSettings.cpp
extern uint16_t PersistentSettingOffset;

template <class T>
class PersistentSetting {
public:
    /*! Constructor
     * \param minimum the minimum value for this setting
     * \param maximum the maximum value for this setting
     * \param defaultValue the default value for this setting
     * \param eepromOffset if -1, place this setting at the EEPROM address immediately 
     *        after the previous setting (or 0 if this invokation is the first). If
     *        zero or more, use the eepromOffset as the address. When choosing the
     *        offset menually, care must be taken to ensure settings to not overlap.
     */
    PersistentSetting(T minimum, T maximum, T defaultValue, int32_t eepromOffset=-1) : 
        _minimum(minimum),
        _maximum(maximum),
        _defaultValue(defaultValue)
    {
        if (eepromOffset < 0) {
            _eepromOffset = PersistentSettingOffset;
        } else {
            _eepromOffset = eepromOffset;
        }
        PersistentSettingOffset = _eepromOffset + sizeof(T);
        this->load();
    }

    /*! Determine if a value is valid or not (within min / max limits).
     *
     * \param v the value to test.
     *
     * \return true if v is a valid value, else false.
     */
    bool isValid(T v) {
        return v >= _minimum && v <= _maximum;
    }

    /*! Reset the setting to its default value.
     *
     * \param saveIt if true, also save the setting to EEPROM.
     */
    void reset(bool saveIt=false) {
        _value = _defaultValue;
        if (saveIt) {
            save();
        }
    }

    /*! Load value from EEPROM, and return it. If the value in EEPROM is not valid, use the default value.
     *
     * \return the loaded value.
     */
    T load() {
#if defined(ESP8266) or defined(ESP32)
#warning ESP EEPROM functionality not yet implemented
#else
        uint8_t* ptr = (uint8_t*)(&_value);
        for (uint8_t i=0; i<sizeof(T); i++) {
            ptr[i] = EEPROM.read(_eepromOffset+i);
        }
#endif
        if (!isValid(_value)) {
            _value = _defaultValue;
        }
        return _value;
    }

    /*! Save the value to EEPROM
     *  Note: we're using the EEPROM.update() call, so EEPROM is only actually
     *  written if the value is different from the value currently in EEPROM. 
     *  This measure is an attempt to reduce wear on the EEPROM
     */
    void save()
    {
#if defined(ESP8266) or defined(ESP32)
#warning ESP EEPROM functionality not yet implemented
#else
        uint8_t* ptr = (uint8_t*)(&_value);
        DB(F("EEPROM write at "));
        DB(_eepromOffset);
        for (uint8_t i=0; i<sizeof(T); i++) {
            DB('+');
            DB(i);
            EEPROM.update(_eepromOffset+i, ptr[i]);
        }
        DBLN('.');
#endif
    }

    /*! Get the current value of the setting
     */
    T get() { return _value; }

    /*! Sets the in-RAM value of the setting.
     *  \param v the value to be set. If v is less than the minimum value or 
     *         greater than the maximum value, no change will be made.
     *  Note: this function does NOT save the new value to EEPROM. To do that, 
     *  save() must be called.
     */
    T operator=(T v) { if (isValid(v)) { _value = v; } return _value; }

    /*! Sets the in-RAM value of the setting.
     *  \param v the value to be set. If v is less than the minimum value or 
     *         greater than the maximum value, no change will be made.
     *  \return true if the value was set successfully, false otherwise (invalid v)
     *  Note: this function does NOT save the new value to EEPROM. To do that, 
     *  save() must be called.
     */
    bool set(T v, bool saveIt=false) { if (isValid(v)) { _value = v; save(); return true; } else { return false; } }

    /*! Get the size in bytes of the setting in EEPROM.
     */
    size_t size() { return sizeof(T); }

    /*! Print values for this setting to serial (if DEBUG is enabled)
     */
    void dump() {
        DB(F("offset=0x"));
        DB(_eepromOffset, HEX);
        DB(F(" min="));
        DB(_minimum);
        DB(F(" max="));
        DB(_maximum);
        DB(F(" value="));
        DBLN(_value);
    }

private:
    uint16_t _eepromOffset;

protected:
    T _value;
    T _minimum;
    T _maximum;
    T _defaultValue;
};

/* Sometimes it is nice to have a name attached to a PersistentSetting, but the String
 * class is a little heavy for many sketches. NamedPersistentSetting adds a name for
 * a PersistentSetting, with the accociated overhead, so only just this if the need the 
 * name.
 */
template <class T>
class NamedPersistentSetting : public PersistentSetting<T> {
public:
    NamedPersistentSetting(T minimum, T maximum, T defaultValue, const char* name, int32_t eepromOffset=-1) :
        PersistentSetting<T>(minimum, maximum, defaultValue, eepromOffset),
        _name(name) {
    }

    const String& getName() { return _name; }
    void dump() {
        DB(_name);
        DB(": ");
        PersistentSetting<T>::dump();
    }

private:
    String _name;
};

