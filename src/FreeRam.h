#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! Get the number of bytes of free memory.
 *
 * \return number of bytes free
 */
uint32_t FreeRam();

#ifdef  __cplusplus
} // extern "C"
#endif

