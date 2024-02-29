/**
 * This is a reimplementation of the stdarg.h
 * c library.
 */

#ifndef _STDIO_H_
#define _STDIO_H_

#include <libc/ctypes.h>
#include <libc/stdarg.h>

/**
 * Print a formatted string to a buffer with maxlen.
 * The args are passed by a va_list.
 * Use -1 to ignore the maxlen of the buffer.
 * If a value cant be printed because the buffer is
 * too small, it will be written %- (only if there is
 * enought space to do it).
 * Return the number of characters written.
 * Currently supported format:
 *  %d %i   :   32 bit signed integer
 *  %u      :   32 bit unsigned integer
 *  %x      :   32 bit unsigned inter printed with base 16
 *  %ld %li :   64 bit signed integer
 *  %lu     :   64 bit unsigned integer
 *  %lx     :   64 bit unsigned inter printed with base 16
 *  %%      :   print the % character.
 */
int64_t vsnprintf(char* buff, char* format, int64_t maxlen, va_list list);

/**
 *  Same of the vsnprintf but without the va_list
 */
int64_t snprintf(char* buff, char* format, uint64_t maxlen, ...);

/**
 * Same of the vsnprintf but without the check of the size of
 * the buffer. It is caller responsability to make sure there
 * is enought buffer.
 */
int64_t vsprintf(char* buff, char* format, va_list list);

/**
 * Same of the snprintf but without the check of the size of
 * the buffer. It is caller responsability to make sure there
 * is enought buffer.
 */
int64_t sprintf(char* buff, char* format, ...);

#endif //_STDIO_H_

