/**
 * This is a reimplementation of the string.h
 * c library.
 */

#ifndef _STRING_H_
#define _STRING_H_

#include <libc/ctypes.h>

/**
 * Copy a string from a source to a destination.
 * It also recive a maxlen to not buffer overflow the
 * destination.
 * It return -1 if the string was not entirely copied.
 * Otherwise it returns the number of characters written.
 */
int64_t strcpy(char* dest, char* source, int64_t maxlen);

/**
 * Get the length of the string.
 */
int64_t strlen(char* s);

/**
 * Convert an unsigned 64bit integer into a string.
 * It also recive the maximum size lf the buffer.
 * If the size of the string if bigger than the buffer
 * size it will do nothing and return 0.
 * Return the number of characters written.
 * If you dont want to use the maxlen, -1 will be the
 * ignore size value.
 */
int8_t utoa(char* buff, uint64_t val, int8_t base, int64_t maxlen);

/**
 * The same of utoa but for signed 64bit integers.
 */
int8_t itoa(char* buff, int64_t val, int8_t base, int64_t maxlen);

/**
 * Set the entire memory block to a value.
 * NOTE: the value is a int but it will be casted to int8_t
 */
void memset(volatile void* buff, int32_t val, uint64_t b);

#endif //_STRING_H_
