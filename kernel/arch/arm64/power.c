
#include <libc/ctypes.h>
#include <arch/arm64/mailbox.h>
#include <arch/arm64/gpio.h>
#include <arch/arm64/power.h>

#define PM_RSTC         ((volatile uint32_t*)(0x3F000000+0x0010001c))
#define PM_RSTS         ((volatile uint32_t*)(0x3F000000+0x00100020))
#define PM_WDOG         ((volatile uint32_t*)(0x3F000000+0x00100024))
#define PM_WDOG_MAGIC   0x5a000000
#define PM_RSTC_FULLRST 0x00000020

void power_shutdown(){
    register uint32_t r;

    for(r = MBOX_EMMC_ID; r <= MBOX_PIXEL_BVD_ID; r++)
        mbox_req(MBOX_CH_PROP, MBOX_TAG_SETPOWER, r);

    for(r = 0; r < GPIO_N_PINS; r++)
        gpio_fsel(r, GPIO_INPUT);

    for(r = 0; r < GPIO_N_PINS; r++)
        gpio_ppud(r, GPIO_P_OFF);

    // power off the SoC (GPU + CPU)
    r = *PM_RSTS;
    r &= ~0xfffffaaa;
    r |= 0x555;
    *PM_RSTS = PM_WDOG_MAGIC | r;
    *PM_WDOG = PM_WDOG_MAGIC | 10;
    *PM_RSTC = PM_WDOG_MAGIC | PM_RSTC_FULLRST;
}

void power_reboot(){
    uint32_t r;

    r = *PM_RSTS; r &= ~0xfffffaaa;
    *PM_RSTS = PM_WDOG_MAGIC | r;
    *PM_WDOG = PM_WDOG_MAGIC | 10;
    *PM_RSTC = PM_WDOG_MAGIC | PM_RSTC_FULLRST;
}
