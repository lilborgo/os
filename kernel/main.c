#include <arch/arm64/uart0.h>
#include <libc/stdio.h>
#include <libc/string.h>
#include <arch/arm64/rand.h>
#include <arch/arm64/time.h>
#include <arch/arm64/power.h>

void kernel_main(){
	uart0_init();
	rand_init();
	char buff[100];

	time_wait_cyc(10);
	uint64_t a = time_bcm_micros();
	time_wait_micros(100);
	time_wait_micros_bcm(100);
	uint64_t b = time_bcm_micros();
	uint64_t c = time_bcm_micros();
	uint64_t d = time_bcm_micros();
	uint64_t e = time_bcm_micros();
	int32_t r = rand_get(0, 10);

	snprintf(buff, "rand: %d %lu %lu %lu %lu %lu\n", 100, r, a, b, c, d, e);

	uart0_puts(buff);

	power_shutdown();
}
