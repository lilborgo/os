#include <io/uart.h>
#include <debug.h>
#include <string.h>

void kernel_main()
{
    char buff[100];
    //unsigned long sp = debug_get_sp();
    uart_init();

    sprintf(buff, "prova: %d, %d\n", 100, -87);

    uart_write(buff);
    while (1);
}
