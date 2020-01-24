#include "FreeRam.h"

#if defined(ARDUINO_ARCH_AVR)

/* Note: code adapted from MemoryFree library, found at https://github.com/McNeight/MemoryFree
 */

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

extern unsigned int __heap_start;
extern void *__brkval;

/*
 *  * The free list structure as maintained by the
 *   * avr-libc memory allocation routines.
 *    */
struct __freelist
{
  size_t sz;
  struct __freelist *nx;
};

/* The head of the free list structure */
extern struct __freelist *__flp;

#include "FreeRam.h"

/* Calculates the size of the free list */
int _freeListSize()
{
  struct __freelist* current;
  int total = 0;
  for (current = __flp; current; current = current->nx)
  {
    total += 2; /* Add two bytes for the memory block's header  */
    total += (int) current->sz;
  }

  return total;
}

uint32_t FreeRam()
{
  int free_memory;
  if ((int)__brkval == 0)
  {
    free_memory = ((int)&free_memory) - ((int)&__heap_start);
  }
  else
  {
    free_memory = ((int)&free_memory) - ((int)__brkval);
    free_memory += _freeListSize();
  }
  return free_memory;
}

#elif defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)

extern "C" {

#if defined(ARDUINO_ARCH_ESP8266)
#include "user_interface.h"
#elif defined(ARDUINO_ARCH_ESP32)
#include "esp_system.h"
#endif

uint32_t FreeRam() {
    return system_get_free_heap_size();
}

}

#endif

