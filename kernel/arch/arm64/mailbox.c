#include <arch/arm64/gpio.h>
#include <arch/arm64/mailbox.h>
#include <libc/stdarg.h>
#include <libc/string.h>

volatile uint32_t  __attribute__((aligned(16))) mbox_msg[MBOX_MSG_SIZE];
static uint32_t mbox_msg_idx;

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

    mbox_msg[0] = mbox_msg_idx*sizeof(uint32_t);
    mbox_msg[mbox_msg_idx] = 0;

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

bool mbox_add(mbox_tag_t tag, ...){
    va_list list;

    va_start(list, tag);

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
        if(MBOX_MSG_SIZE-mbox_msg_idx <= 6){
            return false;
        }
        mbox_msg[mbox_msg_idx] = MBOX_TAG_SETCLKRATE;
        mbox_msg[mbox_msg_idx+1] = 12;
        mbox_msg[mbox_msg_idx+2] = 0;
        mbox_msg[mbox_msg_idx+3] = va_arg(list, uint32_t);
        mbox_msg[mbox_msg_idx+4] = va_arg(list, uint32_t);
        mbox_msg[mbox_msg_idx+5] = va_arg(list, uint32_t);
        mbox_msg_idx += 6;
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
        if(MBOX_MSG_SIZE-mbox_msg_idx <= 6){
            return false;
        }
        mbox_msg[mbox_msg_idx] = MBOX_TAG_SETPOWER;
        mbox_msg[mbox_msg_idx+1] = 8;
        mbox_msg[mbox_msg_idx+2] = 0;
        mbox_msg[mbox_msg_idx+3]= va_arg(list, uint32_t);
        mbox_msg[mbox_msg_idx+4] = va_arg(list, uint32_t);;
        mbox_msg_idx += 5;
        break;
    case MBOX_TAG_GETARMMEM:
        /*
        Request:
            Length: 0
        Response:
            Length: 8
                Value:
                    u32: base address in bytes
                    u32: size in bytes
        */
        if(MBOX_MSG_SIZE-mbox_msg_idx <= 5){
            return false;
        }
        mbox_msg[mbox_msg_idx] = MBOX_TAG_GETARMMEM;
        mbox_msg[mbox_msg_idx+1] = 8;
        mbox_msg[mbox_msg_idx+2] = 0;
        mbox_msg_idx += 5;
        break;
    default:
        return false;
    }

    return true;
}

void mbox_reset(){
    mbox_msg_idx = 2;
    memset(mbox_msg, 0, MBOX_MSG_SIZE*sizeof(uint32_t));
    mbox_msg[0] = 0;
    mbox_msg[1] = MBOX_REQUEST;
}
