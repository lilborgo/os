/**
 * Used to control the uart0.
 * Datasheet pages: 8
*/

#ifndef _UART0_H_
#define _UART0_H_

/**
 *  First, enable the interface with default
 *  parameters.
 */
void uart0_init();

/*
 * Write a single character to the uart interface.
 * NOTE: this function is blocking, it will not
 * return untile the character is written.
 * If the uart is constantly blocked, it will wait.
 */
void uart0_putc(char c);

/**
 *  Read a character from the uart interface.
 *  NOTE: this function is blocking, it will not
 *  return untile a character is recived.
 */
char uart0_getc();

/*
 *  Write a string to uart1.
 *  It also conver the \n character to the \r one.
 */
void uart0_puts(char s[]);

#endif //_UART0_H_
