/**
 * 	This file contains all the functions related to strings-
 */

#ifndef _STRING_H_
#define _STRING_H_

#include <types.h>

/**
 *	Print string to a string
 */
int sprintf(char* str, char* format, ...);


/**
 * 	Convert integer to array.
 * 	Return number of character written.
 */
i32 itoa(char* str, i64 val);

#endif //_STRING_H_
