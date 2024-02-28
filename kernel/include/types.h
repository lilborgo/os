/**
 *	Types of the variable used by the kernel
 */

#ifndef _TYPES_H_
#define _TYPES_H_

//**********************************GENERIC TYPES**********************************

//byte
typedef unsigned char u8;
typedef char i8;
typedef i8 byte;

//half word
typedef unsigned short u16;
typedef short i16;
typedef i16 hword;

//word
typedef unsigned int u32;
typedef int i32;
typedef i32 word;

//double word
typedef unsigned long u64;
typedef long i64;
typedef i64 dword;

//argument list
typedef __builtin_va_list va_list;

//boolean
typedef enum: u8{
    false = 0,
    true = 1
}bool;

//**********************************MEMORY**********************************

//address
typedef u64 addr_t;

//memory
typedef u32 raw32;
typedef u8 raw8;

//**********************************GPIO**********************************

//gpio (page 91-100
typedef u8 gpio_pin_t;
typedef enum: u8{
    GPIO_INPUT = 0,
    GPIO_OUTPUT = 1,
    GPIO_FUNC0 = 4,
    GPIO_FUNC1 = 5,
    GPIO_FUNC2 = 6,
    GPIO_FUNC3 = 7,
    GPIO_FUNC4 = 3,
    GPIO_FUNC5 = 2
}gpio_pin_func_t;

typedef enum: u8{
    GPIO_P_OFF = 0,
    GPIO_PD_ON = 1,
    GPIO_PU_ON = 2
}gpio_pud_mode_t;

//**********************************MAILBOX**********************************

//mailbox chanlles
typedef enum: u8{
    MBOX_CH_POWER = 0,
    MBOX_CH_FB = 1,
    MBOX_CH_VUART = 2,
    MBOX_CH_VCHIQ = 3,
    MBOX_CH_LEDS = 4,
    MBOX_CH_BTNS = 5,
    MBOX_CH_TOUCH = 6,
    MBOX_CH_COUNT = 7,
    MBOX_CH_PROP = 8
}mb_ch_t;

//message for the mailbox
typedef __attribute__((aligned(16))) volatile u32 mb_msg_t;

#endif //_TYPES_H_
