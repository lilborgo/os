#include <types.h>
#include <memory.h>

/**
 *  Write 32 bit to the memory address.
 */
void mem_write32(addr_t addr, u32 val){
    *(u32*)addr = val;
}

/**
 *  Read 32 bit to the memory address.
 */
u32 mem_read32(addr_t addr) { 
    return *(u32*)addr; 
}