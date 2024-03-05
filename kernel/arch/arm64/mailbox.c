#include <arch/arm64/gpio.h>
#include <arch/arm64/mailbox.h>
#include <libc/stdarg.h>
#include <libc/string.h>

volatile uint32_t  __attribute__((aligned(16))) mbox_msg[36];

#define VIDEOCORE_MBOX  (0x3F000000+0x0000B880)
#define MBOX_READ       (volatile uint32_t*)(VIDEOCORE_MBOX+0x0)
#define MBOX_POLL       (volatile uint32_t*)(VIDEOCORE_MBOX+0x10)
#define MBOX_SENDER     (volatile uint32_t*)(VIDEOCORE_MBOX+0x14)
#define MBOX_STATUS     (volatile uint32_t*)(VIDEOCORE_MBOX+0x18)
#define MBOX_CONFIG     (volatile uint32_t*)(VIDEOCORE_MBOX+0x1C)
#define MBOX_WRITE      (volatile uint32_t*)(VIDEOCORE_MBOX+0x20)
#define MBOX_RESPONSE   0x80000000
#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000

bool mbox_call(mbox_ch_t ch){
    uint32_t r = (((uint32_t)((uint64_t)&mbox_msg)&~0xF) | (ch&0xF));

    while(*MBOX_STATUS & MBOX_FULL)
        asm volatile("nop");

    *MBOX_WRITE = r;

    while(1) {
        /* is there a response? */
        while(*MBOX_STATUS & MBOX_EMPTY)
             asm volatile("nop");

        /* is it a response to our message? */
        if(r == *MBOX_READ)
            /* is it a valid successful response? */
            return mbox_msg[1] == MBOX_RESPONSE;
    }
}

bool mbox_req(mbox_ch_t ch, mbox_tag_t tag, ...){
    va_list list;

    va_start(list, tag);

    memset(mbox_msg, 0, MBOX_MSG_SIZE*sizeof(uint32_t));

    switch(tag){
        case MBOX_TAG_SETCLKRATE:
            /*
            Request:
                Length: 12
                Value:
                    u32: clock id
                    u32: rate (in Hz)
                    u32: skip setting turbo
            Response:
                Length: 8
                Value:
                    u32: clock id
                    u32: rate (in Hz)
            */

            mbox_msg[0] = 9 * sizeof(uint32_t);
            mbox_msg[1] = MBOX_REQUEST;
            mbox_msg[2] = MBOX_TAG_SETCLKRATE;
            mbox_msg[3] = 12;
            mbox_msg[4] = 8;
            mbox_msg[5] = va_arg(list, uint32_t);
            mbox_msg[6] = va_arg(list, uint32_t);
            mbox_msg[7] = va_arg(list, uint32_t);
            mbox_msg[8] = 0;
            break;
        case MBOX_TAG_SETPOWER:
            /*
            Request:
                Length: 8
                Value:
                    u32: device id
                    u32: state
                    State:
                        Bit 0: 0=off, 1=on
                        Bit 1: 0=do not wait, 1=wait
                        Bits 2-31: reserved for future use (set to 0)
            Response:
                Length: 8
                Value:
                    u32: device id
                    u32: state
                    State:
                        Bit 0: 0=off, 1=on
                        Bit 1: 0=device exists, 1=device does not exist
                        Bits 2-31: reserved for future use
            */
            mbox_msg[0]= 8 * sizeof(uint32_t);
            mbox_msg[1] = MBOX_REQUEST;
            mbox_msg[2] = MBOX_TAG_SETPOWER;
            mbox_msg[3] = 8;
            mbox_msg[4] = 8;
            mbox_msg[5]= va_arg(list, uint32_t);
            mbox_msg[6] = 0;
            mbox_msg[7] = 0;
        default:
            return false;
    }

    return mbox_call(ch);
}
