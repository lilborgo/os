/**
 * This file is used to enable the communication with the raspberry pi 3b uart.
 * In order to use uart1, the uart_enable must be set to 0 in the config.txt file.
 */

#ifndef _UART1_H_
#define _UART1_H_

/**
 *  Initialize the uart1
 */
void uart1_init();

/*
 * Write character.
 */
void uart1_write(char c);

/**
 *  Read character.
 */
char uart1_getc();

/*
 *  Write a string to uart1
 */
void uart1_puts(char *s);



#endif //_UART1_H_
