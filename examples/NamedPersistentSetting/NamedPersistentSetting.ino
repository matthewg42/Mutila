#include <Arduino.h>
#include <EEPROM.h>
#include <MutilaDebug.h>
#include "Settings.h"

void printHelp()
{
    Serial.println();
    Serial.print("1) Set "); Serial.println(BoolSetting.getName());
    Serial.print("2) Set "); Serial.println(UInt32Setting.getName());
    Serial.print("3) Set "); Serial.println(Int16Setting.getName());
    Serial.print("4) Set "); Serial.println(DoubleSetting.getName());
    Serial.print("5) Set "); Serial.println(FloatSetting.getName());
    Serial.println("p) Print current setting values");
    Serial.println("l) Load settings from EEPROM");
    Serial.println("s) Save settings to EEPROM");
    Serial.println("r) Reset default values");
    Serial.println("a) Print sizeof() for atomic types");
    Serial.println("h) Print this help message\n");
}

void printSettings()
{
    Serial.println();
    BoolSetting.dump();
    UInt32Setting.dump();
    Int16Setting.dump();
    DoubleSetting.dump();
    FloatSetting.dump();
}

void printSizes()
{
    Serial.print("\nsizeof char:       ");  Serial.println(sizeof(char));
    Serial.print("sizeof short:      ");  Serial.println(sizeof(short));
    Serial.print("sizeof int:        ");  Serial.println(sizeof(int));
    Serial.print("sizeof long:       ");  Serial.println(sizeof(long));
    Serial.print("sizeof long long:  ");  Serial.println(sizeof(long long));
    Serial.print("sizeof float:      ");  Serial.println(sizeof(float));
    Serial.print("sizeof double:     ");  Serial.println(sizeof(double));
}

void loadSettings()
{
    Serial.println("\nloading settings");
    BoolSetting.load();
    UInt32Setting.load();
    Int16Setting.load();
    DoubleSetting.load();
    FloatSetting.load();
}

void saveSettings()
{
    Serial.println("\nsaving settings");
    BoolSetting.save();
    UInt32Setting.save();
    Int16Setting.save();
    DoubleSetting.save();
    FloatSetting.save();
}

void resetSettings(bool save)
{
    Serial.print("\nresetting defaults ");
    Serial.println(save ? "(and saving)" : "(not saving)");
    BoolSetting.reset(save);
    UInt32Setting.reset(save);
    Int16Setting.reset(save);
    DoubleSetting.reset(save);
    FloatSetting.reset(save);
}

// Read a character from serial (which is either printable, or newline)
char readChar()
{
    while (true) {
        int c = Serial.read();
        bool ret = false;
        if (c == '\r') {
            c = '\n';
        }
        if ((c >= ' ' && c <= '~') || c == '\n') {
            Serial.print((char)c);
            return (char)c;
        }
    }
}

// Read a string of characters from serial, blocking until newline is sent
String readLine()
{
    String s = "";
    while (true) {
        char c = readChar();
        if (c == '\n' || c == '\r') {
            DB("readLine got: ");
            DBLN(s);
            return s;
        } else {
            s += c;
        }
    }
}

// Read a line and return the value converted to a long
long readInteger()
{
    Serial.print("\nEnter int value> ");
    long l = readLine().toInt();
    DB("read int: ");
    DBLN(l);
    return l;
}

// Read a line and return the value converted to a float
float readFloat()
{
    Serial.print("\nEnter float value> ");
    float f = readLine().toFloat();
    DB("read float: ");
    DBLN(f);
    return f;
}

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\nsetup() start");

    // This is an indicator that the device has never had the settings saved, as
    // the default value in the EEPROM is probably 0x00, 0xFF, or at least some random
    // value which is not MagicNumber...
    if (MagicSetting.get() != MagicNumber) {
        // Save all the settings with their default values
        Serial.println("Magic not set - setting defaults...");
        resetSettings(true);
        MagicSetting.reset(true);
    } else {
        Serial.println("Magic checks out, using existing settings");
    }

    printSettings();
    printHelp();
}

void loop()
{
    Serial.print("\nChoose> ");
    char c = readChar();
    bool success;
    switch (c) {
    case '1':
        success = BoolSetting.set(readInteger());
        Serial.print(success ? "Success - " : "Failure - ");
        Serial.print("Value now: ");
        Serial.println(BoolSetting.get());
        break;
    case '2':
        success = UInt32Setting.set(readInteger());
        Serial.print(success ? "Success - " : "Failure - ");
        Serial.print("Value now: ");
        Serial.println(UInt32Setting.get());
        break;
    case '3':
        success = Int16Setting.set(readInteger());
        Serial.print(success ? "Success - " : "Failure - ");
        Serial.print("Value now: ");
        Serial.println(Int16Setting.get());
        break;
    case '4':
        success = DoubleSetting.set(readFloat());
        Serial.print(success ? "Success - " : "Failure - ");
        Serial.print("Value now: ");
        Serial.println(DoubleSetting.get());
        break;
    case '5':
        success = FloatSetting.set(readFloat());
        Serial.print(success ? "Success - " : "Failure - ");
        Serial.print("Value now: ");
        Serial.println(FloatSetting.get());
        break;
    case 'p':
        printSettings();
        break;
    case 'l':
        loadSettings();
        break;
    case 's':
        saveSettings();
        break;
    case 'r':
        resetSettings(false);
        break;
    case 'a':
        printSizes();       
        break;
    case 'h':
        printHelp();
        break;
    default:
        Serial.print("\nInvalid choice: '");
        Serial.print(c);
        Serial.println('\'');
        return;
        break;
    }
}

