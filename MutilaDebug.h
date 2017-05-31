#pragma once

#include <Arduino.h>

#ifdef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

#ifdef MUTILADEBUG
#define MUTILADEBUG 1
#else
#define MUTILADEBUG 0
#endif

// This for internal Mutila use...
#define _DB(...) \
            do { if (MUTILADEBUG) Serial.print(__VA_ARGS__); } while (0)

#define _DBF(...) \
            do { if (MUTILADEBUG) Serial.printf(__VA_ARGS__); } while (0)

#define _DBLN(...) \
            do { if (MUTILADEBUG) Serial.println(__VA_ARGS__); } while (0)

// For use in user apps...
#define DB(...) \
            do { if (DEBUG) Serial.print(__VA_ARGS__); } while (0)

#define DBF(...) \
            do { if (DEBUG) Serial.printf(__VA_ARGS__); } while (0)

#define DBLN(...) \
            do { if (DEBUG) Serial.println(__VA_ARGS__); } while (0)

