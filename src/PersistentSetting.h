#pragma once

#include <Arduino.h>
#include <MutilaDebug.h>
#include <stdint.h>
#include <EEPROM.h>

extern uint16_t PersistentSettingOffset;

template <class T>
class PersistentSetting {
public:
    /*! Constructor
     * \param minimum the minimum value for this setting
     * \param maximum the maximum value for this setting
     * \param defaultValue the default value for this setting
     * \param count how many instances of the setting should be used for wear levelling.
     * \param eepromOffset if -1, place this setting at the EEPROM address immediately 
     *        after the previous setting (or 0 if this invocation is the first). If
     *        zero or more, use the eepromOffset as the address. When choosing the
     *        offset menually, care must be taken to ensure settings to not overlap.
     */
    PersistentSetting(T minimum, T maximum, T defaultValue, uint8_t count=1, int32_t eepromOffset=-1) : 
        _eepromOffset(eepromOffset),
        _count(count),
        _minimum(minimum),
        _maximum(maximum),
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

    /*! Get the value of type T starting at the specified EEPROM address.
     *
     * \param address the address of the first byte of the value.
     */
    T getValueAt(uint16_t address) {
#if defined(ESP8266) or defined(ESP32)
#warning ESP EEPROM functionality not yet implemented
#else
        T value;
        for (uint8_t i=0; i<sizeof(T); i++) {
            *((uint8_t*)&value+i) = EEPROM.read(address+i);
        }
        return value;
#endif
    }

    /*! Get the address of the counter for specified wear-level index.
     *
     * \param idx is the index of the wear-level structure to get
     */
    uint16_t counterOffset(uint8_t idx) {
        return _eepromOffset + ((uint16_t)idx * (sizeof(T) + sizeof(uint8_t)));
    }

    uint16_t dataOffset(uint8_t idx) {
        return counterOffset(idx) + (_count < 2 ? 0 : 1);
    }

    uint8_t getCurrentIdx() {
#if defined(ESP8266) or defined(ESP32)
#warning ESP EEPROM functionality not yet implemented
#else
        uint8_t i = 0;
        for (uint8_t thisCount = EEPROM.read(counterOffset(i)); 
             i < _count; 
             i++) {
            uint8_t nextCount = EEPROM.read(counterOffset((i+1)%_count));
            if ((uint8_t)(nextCount - thisCount) != 1) {
                return i;
            }
            thisCount = nextCount;
        }
        return 0;
#endif
    }

    /*! Load value from EEPROM, and return it. If the value in EEPROM is not valid, use the default value.
     *
     * \return the loaded value.
     */
    T load() {
        // work out in which wear-levelling slot the last value was written
        uint8_t idx = getCurrentIdx();
        _value = getValueAt(dataOffset(idx));
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
        uint8_t idx = getCurrentIdx();
        if (getValueAt(dataOffset(idx)) == _value) {
            return;
        }

        uint16_t address;
        if (_count > 1) {
            // handle wear levelling
            uint8_t counter = EEPROM.read(counterOffset(idx)); 
            idx = (idx + 1) % _count;
            ++counter;
            address = counterOffset(idx);
            EEPROM.update(address++, counter);
        } else {
            // no wear levelling counters or any of that stuff, just a value
            address = _eepromOffset;
        }

        //DB(F(" EEPROM write at: "));
        //DBLN(address);
        for (uint8_t i=0; i<sizeof(T); i++) {
            EEPROM.update(address++, *((uint8_t*)&_value+i));
        }
#endif
    }

    /*! Get the current value of the setting
     */
    T get() { return _value; }

    /*! Get the minimum value of the setting
     */
    T getMinimum() { return _minimum; }

    /*! Get the maximum value of the setting
     */
    T getMaximum() { return _maximum; }

    /*! Get the default value of the setting
     */
    T getDefault() { return _defaultValue; }

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
    bool set(T v, bool saveIt=false) { 
        if (isValid(v)) { 
            _value = v; 
            if (saveIt) { 
                save();
            } 
            return true; 
        } else { 
            return false; 
        } 
    }

    /*! Get the size in bytes of the setting in EEPROM.
     */
    uint16_t size() { 
        if (_count < 2) { 
            /* when we only have 1 instance, we don't store counters at all, just the value. */
            return sizeof(T); 
        } else { 
            /* we have one counter byte + one data item per wear-level instance. */
            return ( sizeof(uint8_t) + sizeof(T) ) * _count;
        }
    }

    /*! Print values for this setting to serial (if DEBUG is enabled)
     */
    void dump() {
        DB(F("off=0x"));
        DB(_eepromOffset, HEX);
        DB(F(" sz="));
        DB(size());
        DB(F(" min="));
        DB(_minimum);
        DB(F(" max="));
        DB(_maximum);
        DB(F(" val="));
        DBLN(_value);
    }

private:
    uint16_t _eepromOffset;
    uint8_t _count;

protected:
    T _value;
    T _minimum;
    T _maximum;
    T _defaultValue;
};

/* Sometimes it is nice to have a name attached to a PersistentSetting, but the String
 * class is a little heavy for many sketches. NamedPersistentSetting adds a name for
 * a PersistentSetting, with the accociated overhead, so only use this if you need the 
 * name.
 */
template <class T>
class NamedPersistentSetting : public PersistentSetting<T> {
public:
    NamedPersistentSetting(T minimum, T maximum, T defaultValue, const char* name, uint8_t count=1, int32_t eepromOffset=-1) :
        PersistentSetting<T>(minimum, maximum, defaultValue, count, eepromOffset),
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


