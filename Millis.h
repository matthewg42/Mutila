#pragma once

//! A type for Millis()
typedef unsigned long tMillis;

//! Global Millis offset value
extern float _MillisOffsetMs;

//! Replacement for millis()
tMillis Millis(); 

//! Add offset
void addMillisOffset(float ms);


