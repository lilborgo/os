/**
 * This is a reimplementation of the stdbool.h
 * c library.
 */

#ifndef _STDBOOL_H_
#define _STDBOOL_H_

/**
 *  Redefine the builtin boolean type(_Bool)
 *  to a more common type.
 */
#define bool _Bool
#define true 1
#define false 0

#endif //_STDBOOL_H_
