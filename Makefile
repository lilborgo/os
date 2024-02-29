#compiler
CC = aarch64-linux-gnu-gcc
#assembler
AS = aarch64-linux-gnu-as
#linker
LD = aarch64-linux-gnu-ld
#object copy
OBJCP = aarch64-linux-gnu-objcopy
#object dump
OBJDU = aarch64-linux-gnu-objdump
#qemu binary
QEMU = qemu-system-aarch64
#kill qemu if exist
KILL = pkill -9 -f $(QEMU)

#include folder
INC_DIR = kernel/include
#kernel folder
KER_DIR = kernel
#build folder
BUILD_DIR = build
#output name
KR_NAME = kernel-64
#kernel elf
KER_ELF = $(BUILD_DIR)/$(KR_NAME).elf
#kernel img
KER_IMG = $(BUILD_DIR)/$(KR_NAME).img

#gcc flags
CC_FLAGS = -Wall -Wextra -ffreestanding -mcpu=cortex-a53 -mgeneral-regs-only -I $(INC_DIR) -g -ggdb
#assembler flags
AS_FLAGS = -g
#linker flags
LD_FLAGS = -nostdlib
#qemu flags
QM_FLAGS = -machine raspi3b -kernel $(KER_ELF) -serial null -serial stdio
#gdb flags
GDB_FLAGS = $(KER_ELF) -ex "target remote localhost:1234" -ex "lay split" -ex "set scheduler-locking step"


#linker file
LINKER = $(KER_DIR)/link.ld
#object files
SRCS =	$(KER_DIR)/main.c\
	$(KER_DIR)/boot/boot.S\
	$(KER_DIR)/hw/gpio.c\
	$(KER_DIR)/hw/uart1.c\
	$(KER_DIR)/libc/string.c\
	$(KER_DIR)/libc/stdio.c

OBJS =$(SRCS:%=$(BUILD_DIR)/%.o)

kernel: $(KER_ELF)
	@true

$(KER_ELF): $(OBJS)
	@printf "\tLD $(KER_ELF)\n"
	@$(LD) $(LD_FLAGS) $(OBJS) -T $(LINKER) -o $(KER_ELF)

$(KER_IMG): $(KER_ELF)
	@printf "\tOC $(KER_IMG)\n"
	@$(OBJCP) -O binary $(KER_ELF) $(KER_IMG)

qemu: $(KER_ELF)
	$(QEMU) $(QM_FLAGS)

gdb: $(KER_ELF)
	$(QEMU) -s -S $(QM_FLAGS) & gdb $(GDB_FLAGS)
	-$(KILL)

objd:
	@$(OBJDU) -D -s $(KER_ELF) | less

img:
	@bash mk-img.sh

clean:
	@yes | rm -f -r build

$(BUILD_DIR)/%.S.o: %.S
	@printf "\tAS $<\n"
	@mkdir -p $(dir $@)
	@$(AS) $(AS_FLAGS) -c $< -o $@

$(BUILD_DIR)/%.c.o: %.c
	@printf "\tCC $<\n"
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) -c $< -o $@


