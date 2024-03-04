#include <arch/arm64/gpio.h>
#include <arch/arm64/mailbox.h>

volatile uint32_t  __attribute__((aligned(16))) mbox_msg[36];

#define VIDEOCORE_MBOX  (0x3F000000+0x0000B880)
#define MBOX_READ       ((volatile uint32_t*)(VIDEOCORE_MBOX+0x0))
#define MBOX_POLL       ((volatile uint32_t*)(VIDEOCORE_MBOX+0x10))
#define MBOX_SENDER     ((volatile uint32_t*)(VIDEOCORE_MBOX+0x14))
#define MBOX_STATUS     ((volatile uint32_t*)(VIDEOCORE_MBOX+0x18))
#define MBOX_CONFIG     ((volatile uint32_t*)(VIDEOCORE_MBOX+0x1C))
#define MBOX_WRITE      ((volatile uint32_t*)(VIDEOCORE_MBOX+0x20))
#define MBOX_RESPONSE   0x80000000
#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000

bool mailbox_call(uint8_t ch){
    uint32_t r = (((unsigned int)((unsigned long)&mbox_msg)&~0xF) | (ch&0xF));

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

    return false;
}
