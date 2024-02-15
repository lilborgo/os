/**
 * 	This file contains all the function related to the Uart communication.
 *	It can read, write and init the uart port.
 */

#ifndef _UART_H_
#define _UART_H_

/**
 * 	Initilize the uart communitacion.
 */
void uart_init();

/**
 * 	Write string to Uart.
 */
void uart_write(char *buff);

#endif //_UART_H_