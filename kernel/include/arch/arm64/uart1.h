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
