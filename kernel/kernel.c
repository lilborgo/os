
volatile unsigned char *uart = (unsigned char *) 0x09000000;

void putc(char c) {
    *uart = c;
}

void print(char *s) {
    while(*s != '\0') {
        putc(*s);
        s++;
    }
}

void kmain(void) {
     print("Hello world!\n\0");
}
