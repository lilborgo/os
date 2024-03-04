/**
 * Implementation of the mailbox pheriperal.
 * Documentation: https://github.com/raspberrypi/firmware/
*/

#ifndef _MAILBOX_H_
#define _MAILBOX_H_

#include <libc/ctypes.h>
#include <libc/stdbool.h>

extern volatile uint32_t mbox_msg[36];

#define MBOX_REQUEST    0

#define MBOX_CH_POWER   0
#define MBOX_CH_FB      1
#define MBOX_CH_VUART   2
#define MBOX_CH_VCHIQ   3
#define MBOX_CH_LEDS    4
#define MBOX_CH_BTNS    5
#define MBOX_CH_TOUCH   6
#define MBOX_CH_COUNT   7
#define MBOX_CH_PROP    8

#define MBOX_TAG_GETSERIAL      0x10004
#define MBOX_TAG_LAST           0

bool mailbox_call(uint8_t ch);

#endif //_MAILBOX_H
