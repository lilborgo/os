/**
 * Used to control the uart1.
 * This pheriperals is very basic, it can be used
 * without mailbox and is very limitate.
 * Check uart0.
 * Datasheet pages: 8
*/

#ifndef _UART1_H_
#define _UART1_H_

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

/**
 *  First, enable the interface with default
 *  parameters.
 */
void uart1_init();

/*
 * Write a single character to the uart interface.
 * NOTE: this function is blocking, it will not
 * return untile the character is written.
 * If the uart is constantly blocked, it will wait.
 */
void uart1_putc(char c);

/**
 *  Read a character from the uart interface.
 *  NOTE: this function is blocking, it will not
 *  return untile a character is recived.
 */
char uart1_getc();

/*
 *  Write a string to uart1.
 *  It also conver the \n character to the \r one.
 */
void uart1_puts(char s[]);

#endif //_UART1_H_
