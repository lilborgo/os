/**
 * This file contains all the functions and macro used
 * to control the io of the raspberry pi 3b.
 */

#ifndef _IO_H_
#define _IO_H_

#include <types.h>
#include <macros.h>

//**********************************MEMORY**********************************

/**
 *	Write 32bit to the memory address.
 */
void mem_write32(addr_t addr, raw32 val);

/**
 *	Read 32bit from the memory address.
 */
raw32 mem_read32(addr_t addr);

/**
 *	Write 8bit to the memory address.
 */
void mem_write8(addr_t addr, raw8 val);

/**
 *	Read 8bit from the memory address.
 */
raw8 mem_read8(addr_t addr);

/**
 * Copy memory from source do destination.
 */
void mem_cpy(addr_t dest, addr_t source, u64 size);

#define MMIO_BASE       0x3F000000

/**
 *  GPIO registers, check datasheet. (page 90)
 */
#define GPFSEL0         (MMIO_BASE+0x00200000)
#define GPFSEL1         (MMIO_BASE+0x00200004)
#define GPFSEL2         (MMIO_BASE+0x00200008)
#define GPFSEL3         (MMIO_BASE+0x0020000C)
#define GPFSEL4         (MMIO_BASE+0x00200010)
#define GPFSEL5         (MMIO_BASE+0x00200014)
#define GPSET0          (MMIO_BASE+0x0020001C)
#define GPSET1          (MMIO_BASE+0x00200020)
#define GPCLR0          (MMIO_BASE+0x00200028)
#define GPCLR1          (MMIO_BASE+0x0020002C)
#define GPLEV0          (MMIO_BASE+0x00200034)
#define GPLEV1          (MMIO_BASE+0x00200038)
#define GPEDS0          (MMIO_BASE+0x00200040)
#define GPEDS1          (MMIO_BASE+0x00200044)
#define GPFEN0          (MMIO_BASE+0x00200058)
#define GPFEN1          (MMIO_BASE+0x0020005C)
#define GPHEN0          (MMIO_BASE+0x00200064)
#define GPHEN1          (MMIO_BASE+0x00200068)
#define GPLEN0          (MMIO_BASE+0x00200070)
#define GPLEN1          (MMIO_BASE+0x00200074)
#define GPAREN0         (MMIO_BASE+0x0020007C)
#define GPAREN1         (MMIO_BASE+0x00200080)
#define GPAFEN0         (MMIO_BASE+0x00200088)
#define GPAFEN1         (MMIO_BASE+0x0020008C)
#define GPPUD           (MMIO_BASE+0x00200094)
#define GPPUDCLK0       (MMIO_BASE+0x00200098)
#define GPPUDCLK1       (MMIO_BASE+0x0020009C)

/**
 *  Uart register addresses, check datasheet. (page 8)
 */
#define AUX_IRQ             (MMIO_BASE+0x00215000)
#define AUX_ENABLES         (MMIO_BASE+0x00215004)
#define AUX_MU_IO_REG       (MMIO_BASE+0x00215040)
#define AUX_MU_IER_REG      (MMIO_BASE+0x00215044)
#define AUX_MU_IIR_REG      (MMIO_BASE+0x00215048)
#define AUX_MU_LCR_REG      (MMIO_BASE+0x0021504C)
#define AUX_MU_MCR_REG      (MMIO_BASE+0x00215050)
#define AUX_MU_LSR_REG      (MMIO_BASE+0x00215054)
#define AUX_MU_MSR_REG      (MMIO_BASE+0x00215058)
#define AUX_MU_SCRATCH      (MMIO_BASE+0x0021505C)
#define AUX_MU_CNTL_REG     (MMIO_BASE+0x00215060)
#define AUX_MU_STAT_REG     (MMIO_BASE+0x00215064)
#define AUX_MU_BAUD_REG     (MMIO_BASE+0x00215068)

//**********************************GPIO**********************************

/**
 * Set gpio pin function.
 */
void TH_UN gpio_fsel(gpio_pin_t pin, gpio_pin_func_t mode);

/**
 *  Set gpio pin pull up/down.
 */
void TH_UN gpio_ppud(gpio_pin_t pin, gpio_pud_mode_t mode);

//**********************************UART1**********************************

/**
 *  Initialize the uart1
 */
void TH_UN uart1_init();

/*
 * Write character.
 */
void TH_UN uart1_write(char c);

/**
 *  Read character.
 */
char TH_UN uart1_getc();

/*
 *  Write a string to uart1
 */
void TH_UN uart1_puts(char *s);

//**********************************MAILBOX**********************************
//reference: https://github.com/raspberrypi/firmware/wiki

//registers of the MAILBOX
#define MBOX_BASE       (MMIO_BASE+0x0000B880)
#define MBOX_READ       (MBOX_BASE+0x0))
#define MBOX_POLL       (MBOX_BASE+0x10)
#define MBOX_SENDER     (MBOX_BASE+0x14)
#define MBOX_STATUS     (MBOX_BASE+0x18)
#define MBOX_CONFIG     (MBOX_BASE+0x1C)
#define MBOX_WRITE      (MBOX_BASE+0x20)
//mail box status
#define MBOX_RESPONSE   0x80000000
#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000

//positions of the data
#define MBOX_INDX_POS 0
#define MBOX_SIZE_POS 1
#define MBOX_RQRE_POS 2

/**
 * Send the message to the mailbox.
 */
bool mbox_call(mb_ch_t ch, mb_msg_t* mbox);

/**
 *  Init the mailbox message with default parameters.
 */
void mbox_init(mb_msg_t* mbox);

#endif //_IO_H_
