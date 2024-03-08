#include <arch/arm64/power.h>
#include <arch/arm64/uart0.h>
#include <arch/arm64/linker.h>

void kernel_main(){
	uart0_init();

	uart0_dump(&__start, (&__end)-(&__start));

	power_shutdown();
}
