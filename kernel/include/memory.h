/**
 * 	This file contains all the function used to manage raw memory.
 *	You can read and write from memory.
 */


#ifndef _MEMORY_H_
#define _MEMORY_H_

/**
 *	Write 32bit to the memory address.
 */
void mem_write32(addr_t addr, u32 val);


/**
 *	Read 32bit from the memory address.
 */
u32 mem_read32(addr_t addr);

#endif //_MEMORY_H_