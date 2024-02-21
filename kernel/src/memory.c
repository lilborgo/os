#include <memory.h>

/**
 *  Write 32 bit to the memory address.
 */
void inline mem_write32(addr_t addr, raw32 val){
    *(volatile raw32*)addr = val;
}

/**
 *  Read 32 bit to the memory address.
 */
raw32 inline mem_read32(addr_t addr) {
    return *(volatile raw32*)addr;
}
