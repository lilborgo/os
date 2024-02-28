/**
 * 	This file contains all the functions related to strings-
 */

#ifndef _STRING_H_
#define _STRING_H_

#include <types.h>

/**
 *	Print formatted string to a string.
 *  It need also specified the size of the buffer
 *  Returns the number of characted printed.
 *  If something cant be written, it puts %% but its not
 *  always the case.
 */
u64 snprintf(char* buff, char* format, u64 size, ...);

/**
 *	Same of snprintf bug also require a va_list
 */
u64 vsnprintf(char* buff, char* format, u64 size, va_list list);

/**
 *  Copy string from a source to a destination with the max size.
 */
void strcpy(char* dest, char* source, u64 size);

/**
 * Get the length of the string.
 */
u64 strlen(char* s);

/**
 * 	Convert integer to array.
 * 	Return contains the number of digit written.
 *  It requires the size of the buffer
 */
u8 itoa(char* buff, i64 val, i8 base, u64 size);

/**
 * Convert unsigned integer to array.
 * Return contains the number of digit written.
 */
u8 utoa(char* buff, u64 val, i8 base, u64 size);

#endif //_STRING_H_
