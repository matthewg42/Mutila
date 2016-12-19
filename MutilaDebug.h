#pragma once

#ifdef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define DB(...) \
            do { if (DEBUG) Serial.print(__VA_ARGS__); } while (0)

#define DBLN(...) \
            do { if (DEBUG) Serial.println(__VA_ARGS__); } while (0)

