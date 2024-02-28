#include <io.h>
#include <macros.h>

//**********************************MEMORY**********************************

/**
 *  Write 32 bit to the memory address.
 */
inline void mem_write32(addr_t addr, raw32 val){
    *(volatile raw32*)addr = val;
}

/**
 *  Read 32 bit to the memory address.
 */
inline raw32 mem_read32(addr_t addr) {
    return *(volatile raw32*)addr;
}

/**
 *  Write 8 bit to the memory address.
 */
inline void mem_write8(addr_t addr, raw8 val){
    *(volatile raw8*)addr = val;
}

/**
 *  Read 8 bit to the memory address.
 */
inline raw8 mem_read8(addr_t addr) {
    return *(volatile raw8*)addr;
}


/**
 * Copy memory from source do destination.
 */
void mem_cpy(addr_t dest, addr_t source, u64 size){
    while(size){
        mem_write8(dest, mem_read8(source));
        dest++;
        source++;
        size--;
    }
}

//**********************************GPIO**********************************

#define PINS_PER_REG 10
#define FUN_SIZE_BIT 3

static const addr_t GPFSEL_REGS[] = {GPFSEL0, GPFSEL1, GPFSEL2, GPFSEL3, GPFSEL4, GPFSEL5};

void TH_UN gpio_fsel(gpio_pin_t pin, gpio_pin_func_t mode){
    addr_t reg;
    gpio_pin_t rel_pin;
    u8 shift;
    raw32 r;

    //get pin number relative to the register
    rel_pin = pin%PINS_PER_REG;
    //get register relative to the pin
    reg = GPFSEL_REGS[pin/PINS_PER_REG];
    //posizion in bit of the function of the pin
    shift = rel_pin*FUN_SIZE_BIT;

    //read current value of the register
    r = mem_read32(reg);
    //write 000 to the pin position
    r &= ~(7 << shift);
    //write the function to the register
    r |= (mode << shift);

    //write to the register
    mem_write32(reg, r);
}

void TH_UN gpio_ppud(gpio_pin_t pin, gpio_pud_mode_t mode){
    register u16 r;
    addr_t reg;

    //choose witch register use in base of the pin
    reg = pin/32 ? GPPUDCLK1 : GPPUDCLK0;
    //set the mode in the register
    mem_write32(GPPUD, mode);
    //way 150 cycles
    for(r = 150; r; r--)
        NOP;
    //write the pin to apply the change
    mem_write32(reg, 1 << (pin%32));
    //wait 150 cycles
    for(r = 150; r; r--)
        NOP;
    //flush the register
    mem_write32(reg, 0);
}

//**********************************UART1**********************************

/**
 * Set baud rate and characteristics (115200 8N1) and map to GPIO
 */
void TH_UN uart1_init(){
    mem_write32(AUX_ENABLES, 1);
    mem_write32(AUX_MU_CNTL_REG, 0);
    mem_write32(AUX_MU_LCR_REG, 0);
    mem_write32(AUX_MU_MCR_REG, 3);
    mem_write32(AUX_MU_IER_REG, 0);
    mem_write32(AUX_MU_IIR_REG, 0xc6);
    mem_write32(AUX_MU_BAUD_REG, 270);

    gpio_fsel(14, GPIO_FUNC5);
    gpio_fsel(15, GPIO_FUNC5);

    gpio_ppud(14, GPIO_P_OFF);
    gpio_ppud(15, GPIO_P_OFF);

    mem_write32(AUX_MU_CNTL_REG, 3);
}

/**
 * Write char to uart1.
 */
void TH_UN uart1_write(char c) {
    //wait until we can send
    while(!(mem_read32(AUX_MU_LSR_REG)&0x20));
    mem_write32(AUX_MU_IO_REG, c);
}

/**
 * Read a char.
 */
char TH_UN uart1_read() {
    char c;
    //Wait until something is in the buffe
    while(!(mem_read32(AUX_MU_LSR_REG)&0x01));
    c = mem_read32(AUX_MU_IO_REG);
    return c == '\r' ? '\n' : c;
}

/**
 *  Write a string to uart1.
 */
void TH_UN uart1_puts(char *s) {
    while(*s) {
        if(*s=='\n')
            uart1_write('\r');

        uart1_write(*s);
        s++;
    }
}

//**********************************MAILBOX**********************************

//send the message to the channel
bool mbox_call(mb_ch_t ch, mb_msg_t* mbox){
    u32 m;

    mbox[MBOX_SIZE_POS] = (mbox[MBOX_INDX_POS]+1) << 2;
    mbox++;

    //clear the first 4 bit and write the channel to it
    m = (((u32)mbox) & (~0xF)) | ch;

    //wait the mailbox to be empty
    while(mem_read32(MBOX_STATUS) & MBOX_FULL)
        NOP;

    //write the address of the message to the mailbox address
    mem_write32(MBOX_WRITE, m);

    while(1) {
        //wait a responce
        while(mem_read32(MBOX_STATUS) & MBOX_EMPTY)
            NOP;

        //is a message for us?
        if(m == mem_read32(MBOX_READ)
            //check if its a valid request
            return mbox[1] == MBOX_RESPONSE;
    }
    return false;
}

//init the mbox message
void mbox_init(mb_msg_t* mbox){
    //set the index position
    mbox[MBOX_INDX_POS] = 2;

    //set the size of the mailbox
    mbox[MBOX_SIZE_POS] = 12;

    //set to request mode
    mbox[MBOX_RQRE_POS] = 0;

    //null terminator
    mbox[MBOX_RQRE_POS+1] = 0;
}
