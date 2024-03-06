#include <arch/arm64/gpio.h>
#include <arch/arm64/mailbox.h>

#define UART0_DR        ((volatile uint32_t*)(0x3F000000+0x00201000))
#define UART0_FR        ((volatile uint32_t*)(0x3F000000+0x00201018))
#define UART0_IBRD      ((volatile uint32_t*)(0x3F000000+0x00201024))
#define UART0_FBRD      ((volatile uint32_t*)(0x3F000000+0x00201028))
#define UART0_LCRH      ((volatile uint32_t*)(0x3F000000+0x0020102C))
#define UART0_CR        ((volatile uint32_t*)(0x3F000000+0x00201030))
#define UART0_IMSC      ((volatile uint32_t*)(0x3F000000+0x00201038))
#define UART0_ICR       ((volatile uint32_t*)(0x3F000000+0x00201044))

void uart0_init(){
    *UART0_CR = 0;

    mbox_reset();
    mbox_add(MBOX_TAG_SETCLKRATE, MBOX_UART_ID, 4000000, 0);
    mbox_call(MBOX_CH_PROP);

    gpio_fsel(14, GPIO_FUNC0);
    gpio_fsel(15, GPIO_FUNC0);
    gpio_ppud(14, GPIO_P_OFF);
    gpio_ppud(15, GPIO_P_OFF);

    *UART0_ICR = 0x7FF;
    *UART0_IBRD = 2;
    *UART0_FBRD = 0xB;
    *UART0_LCRH = 0x7 << 4;
    *UART0_CR = 0x301;
}

void uart0_putc(char c) {
    //wait until we can send
    while(*UART0_FR & 0x20)
        asm volatile("NOP");

    *UART0_DR = c;
}

char uart0_getc() {
    char c;
    //wait until something is in the buffe
    while(*UART0_FR & 0x01)
        asm volatile("NOP");

    c = (char)*UART0_DR;

    return c == '\r' ? '\n' : c;
}


void uart0_puts(char s[]) {
    while(*s) {
        if(*s == '\n')
            uart0_putc('\r');

        uart0_putc(*s);
        s++;
    }
}

