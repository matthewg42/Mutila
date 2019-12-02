#pragma once

#include <Arduino.h>
#include <MutilaDebug.h>
#include <stdint.h>
#include <EEPROM.h>

extern uint16_t PersistentSettingOffset;

/*! \class PersistentSetting
 *  \brief EEPROM-backed variables with optional wear levelling functionality.
 *
 *  PersistentSetting is a template class that models a value which may be loaded
 *  from and saved to EEPROM. PersistentSettings are constructed with minimum,
 *  maximum and default values. A number of redundant copies used for wear
 *  levelling may also specified, and optionally the address in EEPROM where
 *  the data should be stored. By defaul the address is cauclated as the byte
 *  following the previously-constructed PersistentSetting (or 0 when constructing
 *  the first object).
 *
 *  If the value loaded from EEPROM is invalid (outside the min-max range), the
 *  default value will be set.
 *
 *  After construction, the value of a PersistenSetting may be retrieved with the
 *  get() method, and the value set with the set() method. These operations return
 *  and set the volatile state of the setting. An explicit save() call must be made
 *  to write the setting to EEPROM (or use saveit=true when calling set()).
 *
 *  If the value in EEPROM is the same as the current value, nothing will be
 *  written to EEPROM, although a short delay me be experienced since EEPROM IO
 *  can be comparitively slow.
 *
 *  EEPROM has a limited number of write cycles (~100,000) before failure.
 *  To extend the life of projects which write to EEPROM frequently (e.g. device
 *  usage counters), PersistenSettings implements a simple wear levelling scheme.
 *
 *  To enable wear levelling, specify copies > 1 when constructing a
 *  PersistenSetting. If copies == `n`, The amount of EEPROM space used will be
 *  `(sizeof(T) + 1) * n` where `T` is the type of the data being stored.
 *
 *  For example, a usage counter which we expect to reach 200,000 in the life of
 *  the device might be constructed as follows:
 *
 *  `PersistentSetting<uint32_t> UsageCounter(0, UINT32_MAX, 0, 3);`
 *
 *  Three copies of data are used, so the writes are spread over those copies.
 *  if the device would be used 200,000 times, we would expect ~ 66,000 writes
 *  per instance of the data in the lifetime of the device - safely below the
 *  write limit.
 *
 *  In the EEPROM, the data would be stored as follows:
 *
 *  | Address  | Copy # | Data Stored |
 *  | -------- | ------ | ----------- |
 *  | 0        | 1      | Counter     |
 *  | 1        | 1      | Data Byte 1 |
 *  | 2        | 1      | Data Byte 2 |
 *  | 3        | 1      | Data Byte 3 |
 *  | 4        | 1      | Data Byte 4 |
 *  | 5        | 2      | Counter     |
 *  | 6        | 2      | Data Byte 1 |
 *  | 7        | 2      | Data Byte 2 |
 *  | 8        | 2      | Data Byte 3 |
 *  | 9        | 2      | Data Byte 4 |
 *  | 10       | 3      | Counter     |
 *  | 11       | 3      | Data Byte 1 |
 *  | 12       | 3      | Data Byte 2 |
 *  | 13       | 3      | Data Byte 3 |
 *  | 14       | 3      | Data Byte 4 |
 *
 * The Counter values are used to work out which is the most recently saved
 * instance of the data.
 *
 * NOTE: using wear levelling will increase the time taken for loads and saves
 * propotional to the number of copies.
 *
 * By contrast, with the number of copies == 1, the EEPROM memory layout would
 * look like this:
 *
 *  | Address  | Data Stored |
 *  | -------- | ----------- |
 *  | 0        | Data Byte 1 |
 *  | 1        | Data Byte 2 |
 *  | 2        | Data Byte 3 |
 *  | 3        | Data Byte 4 |
 *
 *
 */

template <class T>
class PersistentSetting {
public:
    /*! Constructor
     * \param minimum the minimum value for this setting.
     * \param maximum the maximum value for this setting.
     * \param defaultValue the default value for this setting.
     * \param copies how many copies of the data should be used for wear levelling.
     * \param eepromOffset if -1, place this setting at the EEPROM address immediately 
     *        after the previous setting (or 0 if this invocation is the first). If
     *        zero or more, use the eepromOffset as the address. When choosing the
     *        offset menually, care must be taken to ensure settings to not overlap.
     */
    PersistentSetting(T minimum, T maximum, T defaultValue, uint8_t copies=1, int32_t eepromOffset=-1) : 
        _eepromOffset(eepromOffset),
        _copies(copies),
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
        return counterOffset(idx) + (_copies < 2 ? 0 : 1);
    }

    uint8_t getCurrentIdx() {
#if defined(ESP8266) or defined(ESP32)
#warning ESP EEPROM functionality not yet implemented
#else
        uint8_t i = 0;
        for (uint8_t thisCount = EEPROM.read(counterOffset(i)); 
             i < _copies; 
             i++) {
            uint8_t nextCount = EEPROM.read(counterOffset((i+1)%_copies));
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
        if (_copies < 2) {
            // no wear levelling counters or any of that stuff, just a value
            address = _eepromOffset;
        } else {
            // handle wear levelling
            uint8_t counter = EEPROM.read(counterOffset(idx)); 
            idx = (idx + 1) % _copies;
            ++counter;
            address = counterOffset(idx);
            EEPROM.update(address++, counter);
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
        if (_copies < 2) { 
            /* when we only have 1 instance, we don't store counters at all, just the value. */
            return sizeof(T); 
        } else { 
            /* we have one counter byte + one data item per wear-level instance. */
            return ( sizeof(uint8_t) + sizeof(T) ) * _copies;
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
    uint8_t _copies;

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
    NamedPersistentSetting(T minimum, T maximum, T defaultValue, const char* name, uint8_t copies=1, int32_t eepromOffset=-1) :
        PersistentSetting<T>(minimum, maximum, defaultValue, copies, eepromOffset),
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


