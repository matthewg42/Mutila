#pragma once

#include <stdint.h>

/*! \brief Calculate voltage from voltage divider 
 * \param value result of an analogRead in range 0 - 1023
 * \param r1KOhm resistor 1 value in k-ohms
 * \param r2KOhm resistor 2 value in k-ohms
 * \param vRef voltage reference - typically Arduino Vdd
 * \return voltage accross the whole voltage divider in volts
 */
float vDivVolts(const int value, const uint16_t r1KOhm, const uint16_t r2KOhm, const float vRef=5.0);

/*! \brief Allegro ACS756SCB-050B-PFF-T Bi-directional 50A hall effect sensor current calculation
 * \param value result of an analogRead in range 0 - 1023
 * \param vSupply supply voltage
 * \param vRef voltage reference - typically Arduino Vdd
 * \param iOffset current offset 
 * \return current in amps
 */
float currentConversion(const int value, const float vSupply, const float vRef=5.0, const float iOffset=0.028);

