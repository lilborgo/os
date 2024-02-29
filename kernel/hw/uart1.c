#include <hw/gpio.h>
#include <hw/uart1.h>

void uart1_init(){
    *AUX_ENABLES = 1;
    *AUX_MU_CNTL_REG = 0;
    *AUX_MU_LCR_REG = 0;
    *AUX_MU_MCR_REG = 3;
    *AUX_MU_IER_REG = 0;
    *AUX_MU_IIR_REG = 0xc6;
    *AUX_MU_BAUD_REG = 270;

    gpio_fsel(14, GPIO_FUNC5);
    gpio_fsel(15, GPIO_FUNC5);

    gpio_ppud(14, GPIO_P_OFF);
    gpio_ppud(15, GPIO_P_OFF);

    *AUX_MU_CNTL_REG = 3;
}

void uart1_putc(char c) {
    //wait until we can send
    while(!((*AUX_MU_LSR_REG) & 0x20))
        asm volatile("NOP");

    *AUX_MU_IO_REG = c;
}

char uart1_getc() {
    char c;
    //wait until something is in the buffe
    while(!((*AUX_MU_LSR_REG) & 0x01))
        asm volatile("NOP");

    c = (char)*AUX_MU_IO_REG;

    return c == '\r' ? '\n' : c;
}

void uart1_puts(char s[]) {
    while(*s) {
        if(*s == '\n')
            uart1_putc('\r');

        uart1_putc(*s);
        s++;
    }
}
