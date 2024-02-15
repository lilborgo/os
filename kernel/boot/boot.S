.section ".text.boot"

.global _start
_start:
    // Check processor ID is zero (executing on main core), else hang
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, main_core
    b halt
main_core:
    // Set stack to start below our code
    ldr     x1, =__stack
    mov     sp, x1
    bl init_bss
    //call kernel main
    nop
    bl kernel_main
    b halt

init_bss:
    ldr     x1, =__bss_start
    ldr     w2, =__bss_size
loop:
    cbz     w2, end
    str     xzr, [x1], #8
    sub     w2, w2, #1
    cbnz    w2, loop
end:
    ret

halt:
    b halt
