#include <debug.h>

.global debug_get_sp

/**
 *	Return the current stack pointer
 */
debug_get_sp:
	mov x0, sp
	ret
