/**
 *    Shutdown or reboot the raspberry pi.
 */

#ifndef _POWER_H_
#define _POWER_H_

/**
 * Shutdown the board.
 * NOTE: this function will never return.
 */
void power_shutdown();

/**
 * Reboot the raspberry pi.
 * NOTE: this function will never return.
 */
void power_reboot();

#endif //_POWER_H_
