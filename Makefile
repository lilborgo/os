include .config
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

#convert .config file into macros
CC_MACRO = $(awk -F'=' '/^[^#]/ {printf "-D"$1"=" $2" " }' .config)
#gcc flags
CC_FLAGS = -Wall -Wextra -ffreestanding $(CC_MACRO) $(CF_EXTRA) -I $(INC_DIR) -g -ggdb
#assembler flags
AS_FLAGS = -g
#linker flags
LD_FLAGS = -nostdlib
#qemu flags
QM_FLAGS = -machine raspi3b -kernel $(KER_ELF) -serial stdio
#gdb flags
GDB_FLAGS = $(KER_ELF) -ex "target remote localhost:1234" -ex "lay split" -ex "set scheduler-locking step"

#linker file
LINKER = $(KER_DIR)/link.ld

#object files
include $(KER_DIR)/make
SRCS = 	$(LIBC_SRCS)\
	$(ARM64_SRCS)\
	$(KER_DIR)/main.c

OBJS =$(SRCS:%=$(BUILD_DIR)/%.o)

all: kernel

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

qemu-shell: $(KER_ELF)
	@bash execute.sh "$(QEMU) -s -S $(QM_FLAGS)" &

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


