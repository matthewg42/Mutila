#pragma once

#include <Arduino.h>

#ifndef DEBUGSTREAM
#define DEBUGSTREAM Serial
#endif

#ifndef DEBUGBAUD
#define DEBUGBAUD 115200
#endif

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
            do { if (MUTILADEBUG) DEBUGSTREAM.print(__VA_ARGS__); } while (0)

#define _DBF(...) \
            do { if (MUTILADEBUG) DEBUGSTREAM.printf(__VA_ARGS__); } while (0)

#define _DBLN(...) \
            do { if (MUTILADEBUG) DEBUGSTREAM.println(__VA_ARGS__); } while (0)

// For use in user apps...
#define DBBEGIN do { DEBUGSTREAM.begin(DEBUGBAUD); } while (0)

#define DB(...) \
            do { if (DEBUG) DEBUGSTREAM.print(__VA_ARGS__); } while (0)

#define DBF(...) \
            do { if (DEBUG) DEBUGSTREAM.printf(__VA_ARGS__); } while (0)

#define DBLN(...) \
            do { if (DEBUG) DEBUGSTREAM.println(__VA_ARGS__); } while (0)

