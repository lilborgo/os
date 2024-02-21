/**
 *	Types of the variable used by the kernel
 */

#ifndef _TYPES_H_
#define _TYPES_H_

//byte
typedef unsigned char u8;
typedef char i8;
typedef i8 byte;

//half word
typedef unsigned short u16;
typedef short i16;
typedef i16 hword;

//word
typedef unsigned int u32;
typedef int i32;
typedef i32 word;

//double word
typedef unsigned long u64;
typedef long i64;
typedef i64 dword;

//address
typedef u64 addr_t;

//argument list
typedef __builtin_va_list va_list;

//boolean
typedef u8 bool;
#define false 0
#define true 1

//memory
typedef u32 raw32;

#endif //_TYPES_H_
