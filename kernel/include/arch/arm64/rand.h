/**
 * This file contains the hardware random function.
 */

#ifndef _RAND_H_
#define _RAND_H_

#include <libc/ctypes.h>

/**
 * Initialize the hardware random.
 */
void rand_init();

/**
 * Return a random number between min and max
 */
uint32_t rand_get(uint32_t min, uint32_t max);

#endif //_RAND_H_
