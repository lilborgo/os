#include <arch/arm64/rand.h>

#define RNG_CTRL        ((volatile uint32_t*)(0x3F000000+0x00104000))
#define RNG_STATUS      ((volatile uint32_t*)(0x3F000000+0x00104004))
#define RNG_DATA        ((volatile uint32_t*)(0x3F000000+0x00104008))
#define RNG_INT_MASK    ((volatile uint32_t*)(0x3F000000+0x00104010))

void rand_init(){
    *RNG_STATUS = 0x40000;
    *RNG_INT_MASK |= 1;
    *RNG_CTRL |= 1;
}

uint32_t rand_get(uint32_t min, uint32_t max){
    while(!((*RNG_STATUS) >> 24))
        asm volatile("nop");
    return *RNG_DATA % (max - min) + min;
}
