.section ".text.boot"

// Make _start global.
.globl _start
// Entry point for the kernel. Registers:
// x0 -> 32 bit pointer to DTB in memory (primary core only) / 0 (secondary cores)
// x1 -> 0
// x2 -> 0
// x3 -> 0
// x4 -> 32 bit kernel entry point, _start location
_start:
    // set stack before our code
    ldr     x5, =_start
    mov     sp, x5

    bl check_core
    bl clear_bss
    bl kernel_main
    b halt

halt:
    wfe
    b halt

check_core:
    mrs     x5, mpidr_el1
    and     x5, x5, #3
    cbnz     x5, halt
    ret

clear_bss:
    ldr     x5, =__bss_start
    ldr     w6, =__bss_size
loop:
    cbz     w6, end
    str     xzr, [x5], #8
    sub     w6, w6, #1
    cbnz    w6, loop
end:
    ret
