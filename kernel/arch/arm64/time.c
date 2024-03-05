 #include <arch/arm64/time.h>

#define SYSTMR        ((volatile uint64_t*)(0x3F000000+0x00003004))

void time_wait_cyc(uint64_t n){
    while(n){
        asm volatile("nop");
        n--;
    }
}

void time_wait_micros(uint64_t n){
    register unsigned long f, t, r, i;
    asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));
    asm volatile ("mrs %0, cntpct_el0" : "=r"(t));
    i = ( (f / 1000) * n) / 1000;

    do{
        asm volatile ("mrs %0, cntpct_el0" : "=r"(r));
    }while(r-t<i);
}

uint64_t time_bcm_micros(){
    return *SYSTMR;
}

void time_wait_micros_bcm(uint64_t n){
    register uint64_t t;

    t = time_bcm_micros();

    while(time_bcm_micros()-t < n);
}
