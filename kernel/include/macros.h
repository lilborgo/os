/**
 *  This file contains all the macros used in the code.
 */

#ifndef _MACROS_H_
#define _MACROS_H_

//initialize va list
#define va_start(v, l)	__builtin_va_start(v,l)
//get next argument
#define va_arg(v, t)	__builtin_va_arg(v, t)
//copy va list
#define va_copy(d, s)	__builtin_va_copy(d, s)

//get absolute value
#define ABS(x) (x > 0 ? x : -x)
//get min
#define MIN(x, y) (x < y ? x : y)
//get max
#define MAX(x, y) (x > y ? x : y)

//assembly code
#define ASM(c) asm volatile(c)
//nop instruction
#define NOP ASM("nop")

//thread unsafe
#define TH_UN
//thread safe
#define TH_SA

#endif //_MACROS_H_
