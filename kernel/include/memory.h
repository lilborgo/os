/**
 * 	This file contains all the function used to manage raw memory.
 *	You can read and write from memory.
 */

#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <types.h>

/**
 *	Write 32bit to the memory address.
 */
void mem_write32(addr_t addr, raw32 val);


/**
 *	Read 32bit from the memory address.
 */
raw32 mem_read32(addr_t addr);


#define MMIO_BASE       0x3F000000

/**
 *  GPIO registers, check datasheet.
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
 *  Uart register addresses, check datasheet.
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

#endif //_MEMORY_H_
