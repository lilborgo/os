#include <arch/arm64/gpio.h>
#include <arch/arm64/uart1.h>

/**
 *  Uart register addresses. Used to comunicate with
 *  the uart interface.
 */
#define AUX_IRQ             (volatile uint32_t*)(0x3F000000+0x00215000)
#define AUX_ENABLES         (volatile uint32_t*)(0x3F000000+0x00215004)
#define AUX_MU_IO_REG       (volatile uint32_t*)(0x3F000000+0x00215040)
#define AUX_MU_IER_REG      (volatile uint32_t*)(0x3F000000+0x00215044)
#define AUX_MU_IIR_REG      (volatile uint32_t*)(0x3F000000+0x00215048)
#define AUX_MU_LCR_REG      (volatile uint32_t*)(0x3F000000+0x0021504C)
#define AUX_MU_MCR_REG      (volatile uint32_t*)(0x3F000000+0x00215050)
#define AUX_MU_LSR_REG      (volatile uint32_t*)(0x3F000000+0x00215054)
#define AUX_MU_MSR_REG      (volatile uint32_t*)(0x3F000000+0x00215058)
#define AUX_MU_SCRATCH      (volatile uint32_t*)(0x3F000000+0x0021505C)
#define AUX_MU_CNTL_REG     (volatile uint32_t*)(0x3F000000+0x00215060)
#define AUX_MU_STAT_REG     (volatile uint32_t*)(0x3F000000+0x00215064)
#define AUX_MU_BAUD_REG     (volatile uint32_t*)(0x3F000000+0x00215068)

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
