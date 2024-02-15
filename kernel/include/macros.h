#ifndef _MACROS_H_
#define _MACROS_H_

#define va_start(v,l)	__builtin_va_start(v,l)
#define va_arg(v,l)	__builtin_va_arg(v,l)
#define va_copy(d,s)	__builtin_va_copy(d,s)

#endif //_MACROS_H_