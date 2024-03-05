/**
 * This file contains everything used to control the gpio interface.
 * The gpio of the raspberry pi 3b is controlled from particuolar
 * registers.
 * Datasheet pages: 90-100.
 */

#ifndef _GPIO_H_
#define _GPIO_H_

#include <libc/ctypes.h>

/**
 *  GPIO registers. Used to control the gpio interface.
 */
#define GPFSEL0         (volatile uint32_t*)(0x3F000000+0x00200000)
#define GPFSEL1         (volatile uint32_t*)(0x3F000000+0x00200004)
#define GPFSEL2         (volatile uint32_t*)(0x3F000000+0x00200008)
#define GPFSEL3         (volatile uint32_t*)(0x3F000000+0x0020000C)
#define GPFSEL4         (volatile uint32_t*)(0x3F000000+0x00200010)
#define GPFSEL5         (volatile uint32_t*)(0x3F000000+0x00200014)
#define GPSET0          (volatile uint32_t*)(0x3F000000+0x0020001C)
#define GPSET1          (volatile uint32_t*)(0x3F000000+0x00200020)
#define GPCLR0          (volatile uint32_t*)(0x3F000000+0x00200028)
#define GPCLR1          (volatile uint32_t*)(0x3F000000+0x0020002C)
#define GPLEV0          (volatile uint32_t*)(0x3F000000+0x00200034)
#define GPLEV1          (volatile uint32_t*)(0x3F000000+0x00200038)
#define GPEDS0          (volatile uint32_t*)(0x3F000000+0x00200040)
#define GPEDS1          (volatile uint32_t*)(0x3F000000+0x00200044)
#define GPFEN0          (volatile uint32_t*)(0x3F000000+0x00200058)
#define GPFEN1          (volatile uint32_t*)(0x3F000000+0x0020005C)
#define GPHEN0          (volatile uint32_t*)(0x3F000000+0x00200064)
#define GPHEN1          (volatile uint32_t*)(0x3F000000+0x00200068)
#define GPLEN0          (volatile uint32_t*)(0x3F000000+0x00200070)
#define GPLEN1          (volatile uint32_t*)(0x3F000000+0x00200074)
#define GPAREN0         (volatile uint32_t*)(0x3F000000+0x0020007C)
#define GPAREN1         (volatile uint32_t*)(0x3F000000+0x00200080)
#define GPAFEN0         (volatile uint32_t*)(0x3F000000+0x00200088)
#define GPAFEN1         (volatile uint32_t*)(0x3F000000+0x0020008C)
#define GPPUD           (volatile uint32_t*)(0x3F000000+0x00200094)
#define GPPUDCLK0       (volatile uint32_t*)(0x3F000000+0x00200098)
#define GPPUDCLK1       (volatile uint32_t*)(0x3F000000+0x0020009C)

/**
 * Number of pins of the raspberry pi.
 */
#define GPIO_N_PINS 54

typedef uint8_t gpio_pin_t;

typedef enum: uint8_t{
    GPIO_INPUT = 0,
    GPIO_OUTPUT = 1,
    GPIO_FUNC0 = 4,
    GPIO_FUNC1 = 5,
    GPIO_FUNC2 = 6,
    GPIO_FUNC3 = 7,
    GPIO_FUNC4 = 3,
    GPIO_FUNC5 = 2
}gpio_pin_func_t;

typedef enum: uint8_t{
    GPIO_P_OFF = 0,
    GPIO_PD_ON = 1,
    GPIO_PU_ON = 2
}gpio_pud_mode_t;

/**
 * Set a particular function to a specified pin.
 * See datasheet.
 */
void gpio_fsel(gpio_pin_t pin, gpio_pin_func_t mode);

/**
 *  Enable/Disable pull up or pull down mode for the pins.
 */
void gpio_ppud(gpio_pin_t pin, gpio_pud_mode_t mode);

#endif //_GPIO_H_
