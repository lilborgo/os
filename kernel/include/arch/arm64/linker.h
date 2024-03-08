/**
 * This file contains the linker variable used in the linker script.
 */

#ifndef _LINKER_H_
#define _LINKER_H_

#include <libc/ctypes.h>

extern uint8_t __start;
extern uint8_t __text_start;
extern uint8_t __text_end;
extern uint8_t __rodata_start;
extern uint8_t __rodata_end;
extern uint8_t __data_start;
extern uint8_t __data_end;
extern uint8_t __bss_start;
extern uint8_t __bss_end;
extern uint8_t __end;

#endif //_LINKER_H_
