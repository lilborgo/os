#include <arch/arm64/uart0.h>
#include <libc/stdio.h>

void kernel_main(){
	uart0_init();
	char buff[115];

	snprintf(buff, "Hello kernel world! %d %ld %u %lu 0x%x 0x%lx %%", 115,
		(int32_t)2147483647,
		(int64_t)9223372036854775807,
		(uint32_t)4294967295,
		(uint64_t)9223372036854775807 << 1,
		(uint32_t)2389428,
		(uint64_t)24398234829347
	);

	uart0_puts(buff);

	while(1);
}
