#include <io/uart1.h>

void kernel_main(){

	uart1_init();
	uart1_puts("Hello, kernel World!\r\n");

	while (1);
}
