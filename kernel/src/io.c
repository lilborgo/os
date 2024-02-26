#include <io.h>
#include <macros.h>

//**********************************MEMORY**********************************

/**
 *  Write 32 bit to the memory address.
 */
inline void mem_write32(addr_t addr, raw32 val){
    *(volatile raw32*)addr = val;
}

/**
 *  Read 32 bit to the memory address.
 */
inline raw32 mem_read32(addr_t addr) {
    return *(volatile raw32*)addr;
}

//**********************************GPIO**********************************

#define PINS_PER_REG 10
#define FUN_SIZE_BIT 3

static const addr_t GPFSEL_REGS[] = {GPFSEL0, GPFSEL1, GPFSEL2, GPFSEL3, GPFSEL4, GPFSEL5};

void gpio_fsel(gpio_pin pin, gpio_pin_func mode){
    addr_t reg;
    gpio_pin rel_pin;
    u8 shift;
    raw32 r;

    //get pin number relative to the register
    rel_pin = pin%PINS_PER_REG;
    //get register relative to the pin
    reg = GPFSEL_REGS[pin/PINS_PER_REG];
    //posizion in bit of the function of the pin
    shift = rel_pin*FUN_SIZE_BIT;

    //read current value of the register
    r = mem_read32(reg);
    //write 000 to the pin position
    r &= ~(7 << shift);
    //write the function to the register
    r |= (mode << shift);

    //write to the register
    mem_write32(reg, r);
}

void gpio_ppud(gpio_pin pin, gpio_pud_mode mode){
    register u16 r;
    addr_t reg;

    //choose witch register use in base of the pin
    reg = pin/32 ? GPPUDCLK1 : GPPUDCLK0;
    //set the mode in the register
    mem_write32(GPPUD, mode);
    //way 150 cycles
    for(r = 150; r; r--)
        NOP;
    //write the pin to apply the change
    mem_write32(reg, 1 << (pin%32));
    //wait 150 cycles
    for(r = 150; r; r--)
        NOP;
    //flush the register
    mem_write32(reg, 0);
}

//**********************************UART1**********************************

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

    gpio_fsel(14, GPIO_FUNC5);
    gpio_fsel(15, GPIO_FUNC5);

    gpio_ppud(14, GPIO_P_OFF);
    gpio_ppud(15, GPIO_P_OFF);

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
