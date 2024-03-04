/**
 * Implementation of the mailbox pheriperal.
 * Documentation: https://github.com/raspberrypi/firmware/
 *
 *
    Buffer contents:
    - u32: buffer size in bytes (including the header values, the end tag and padding)
    - u32: buffer request/response code
        - Request codes:
            0x00000000: process request
            All other values reserved
        - Response codes:
            0x80000000: request successful
            0x80000001: error parsing request buffer (partial response)
            All other values reserved
    - u8...: sequence of concatenated tags
    - u32: 0x0 (end tag)
    - u8...: padding

    Tag format:
    - u32: tag identifier
    - u32: value buffer size in bytes
    - u32:
        - Request codes:
            b31 clear: request
            b30-b0: reserved
        - Response codes:
            b31 set: response
            b30-b0: value length in bytes
    - u8...: value buffer
    - u8...: padding to align the tag to 32 bits.

*/

#ifndef _MAILBOX_H_
#define _MAILBOX_H_

#include <libc/ctypes.h>
#include <libc/stdbool.h>
#include <libc/stdbool.h>

/**
 * Size of the mailbox max size
 */
#define MBOX_MSG_SIZE 36

/**
 * Mailbox message.
 * This should be used only by the library.
 */
extern volatile uint32_t mbox_msg[MBOX_MSG_SIZE];

/**
 * Request code.
 */
#define MBOX_REQUEST    0

/**
 * Channel used to get property data.
 */
typedef enum: uint8_t{
    MBOX_CH_PROP = 8
}mbox_ch_t;

/**
 * Types of tags for the mailbox.
 */
typedef enum: uint32_t{
    MBOX_TAG_SETCLKRATE = 0x00038002
}mbox_tag_t;

typedef enum: uint32_t{
    MBOX_UART_ID = 0x000000002
}mbox_clkrate_id_t;

/**
 * Send the message to the channel and wait
 * for a response.
 */
bool mbox_call(mbox_ch_t ch);

/**
 * Create the message data structure and send to
 * the channel.
 */
bool mbox_req(mbox_ch_t ch, mbox_tag_t tag, ...);

#endif //_MAILBOX_H
