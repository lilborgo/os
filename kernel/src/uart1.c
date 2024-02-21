#include <io/uart1.h>
#include <memory.h>
#include <macros.h>

/**
 * Set baud rate and characteristics (115200 8N1) and map to GPIO
 */
void uart1_init(){
    register u32 r;

    mem_write32(AUX_ENABLES, 1);
    mem_write32(AUX_MU_CNTL_REG, 0);
    mem_write32(AUX_MU_LCR_REG, 0);
    mem_write32(AUX_MU_MCR_REG, 3);
    mem_write32(AUX_MU_IER_REG, 0);
    mem_write32(AUX_MU_IIR_REG, 0xc6);
    mem_write32(AUX_MU_BAUD_REG, 270);

/*   map UART1 to GPIO pins */
    r = mem_read32(GPFSEL1);
    r &= ~((7<<12)|(7<<15)); // gpio14, gpio15
    r |= (2<<12)|(2<<15);    // alt5
    mem_write32(GPFSEL1, r);

    mem_write32(GPPUD, 0);            // enable pins 14 and 15
    r = 150;
    while(r--)
        NOP;
    mem_write32(GPPUDCLK0,(1<<14)|(1<<15));
    r=150;
    while(r--)
        NOP;
    mem_write32(GPPUDCLK0, 0);        // flush GPIO setup

    mem_write32(AUX_MU_CNTL_REG, 3);
}

/**
 * Write char to uart1.
 */
void uart1_write(char c) {
    //wait until we can send
    while(!(mem_read32(AUX_MU_LSR_REG)&0x20));
    mem_write32(AUX_MU_IO_REG, c);
}

/**
 * Read a char.
 */
char uart1_read() {
    char c;
    //Wait until something is in the buffe
    while(!(mem_read32(AUX_MU_LSR_REG)&0x01));
    c = mem_read32(AUX_MU_IO_REG);
    return c == '\r' ? '\n' : c;
}

/**
 *  Write a string to uart1.
 */
void uart1_puts(char *s) {
    while(*s) {
        if(*s=='\n')
            uart1_write('\r');

        uart1_write(*s);
        s++;
    }
}
