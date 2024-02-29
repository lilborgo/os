#include <hw/gpio.h>

//number of pins controlled by a singular register
#define PINS_PER_REG 10
#define FUN_SIZE_BIT 3

static const volatile uint32_t* GPFSEL[] = {GPFSEL0, GPFSEL1, GPFSEL2, GPFSEL3, GPFSEL4, GPFSEL5};

void gpio_fsel(gpio_pin_t pin, gpio_pin_func_t mode){
    volatile uint32_t* reg;
    gpio_pin_t rel_pin;
    uint8_t shift;
    uint32_t r;

    //get pin number relative to the register
    rel_pin = pin%PINS_PER_REG;
    //get register relative to the pin
    reg = (volatile uint32_t*)GPFSEL[pin/PINS_PER_REG];
    //posizion in bit of the function of the pin
    shift = rel_pin*FUN_SIZE_BIT;

    //read current value of the register
    r = *reg;
    //write 000 to the pin position
    r &= ~(7 << shift);
    //write the function to the register
    r |= (mode << shift);

    //write to the register
    *reg = r;
}

void gpio_ppud(gpio_pin_t pin, gpio_pud_mode_t mode){
    register uint16_t r;
    volatile uint32_t* reg;

    //choose witch register use in base of the pin
    reg = pin/32 ? GPPUDCLK1 : GPPUDCLK0;
    //set the mode in the register
    *GPPUD = mode;
    //way 150 cycles
    for(r = 150; r; r--)
        asm volatile("NOP");
    //write the pin to apply the change
    *reg = 1 << (pin%32);
    //wait 150 cycles
    for(r = 150; r; r--)
        asm volatile("NOP");
    //flush the register
    *reg = 0;
}
