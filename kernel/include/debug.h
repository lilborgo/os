/**
 * 	This file contains the functions related to debug the kernel 
 * 	and logging.
 * 	Here you can read useful registets and other functionality.
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <types.h>

/**
 *	Return the current stack pointer value
 */
addr_t debug_get_sp();

#endif //_DEBUG_H_