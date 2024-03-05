/**
 * This file contains the interaction with the time for the hardware.
 */
#ifndef _TIME_H_
#define _TIME_H_

#include <libc/ctypes.h>

/**
 * Wait N CPU cycles.
 */
void time_wait_cyc(uint64_t n);

/**
 * Wait N microseconds.
 */
void time_wait_micros(uint64_t n);

/**
 * Get BCM timer's counter.
 */
uint64_t time_bcm_micros();

/**
 * Wait N microsec with BCM timer
 */
void time_wait_micros_bcm(uint64_t n);

#endif //_TIME_H_
