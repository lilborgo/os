/**
 * This is a reimplementation of the stdarg.h
 * c library.
 */

#ifndef _STDARG_H_
#define _STDARG_H_

//initialize va list
#define va_start(v, l)	__builtin_va_start(v,l)
//get next argument
#define va_arg(v, t)	__builtin_va_arg(v, t)
//copy va list
#define va_copy(d, s)	__builtin_va_copy(d, s)

typedef __builtin_va_list va_list;


#endif //_STDARG_H_
