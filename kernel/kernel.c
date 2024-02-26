#include <io.h>
#include <string.h>

void kernel_main(){
	char buff[200];
	int b;

	uart1_init();

	b = snprintf(buff, "Hello, Kernel World! %u %d %ld %lu %x %lx\n", 200,
			(u32)4294967295,
			(i32)-2147483647,
			(i64)-9223372036854775807,
			(u64)18446744073709551615,
			(u32)2329384220,
			(u64)15446744073103551633
	);

	uart1_puts(buff);

	while(1);
}
