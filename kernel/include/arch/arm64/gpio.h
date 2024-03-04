/**
 * This file contains everything used to control the gpio interface.
 * The gpio of the raspberry pi 3b is controlled from particuolar
 * registers.
 * Datasheet pages: 90-100.
 */

#ifndef _GPIO_H_
#define _GPIO_H_

#include <libc/ctypes.h>

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
