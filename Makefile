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
#kernel name
KERNEL=kernel8
#kernel elf
KERNEL_ELF=$(KERNEL).elf
#kernel img
KERNEL_IMG=$(KERNEL).img

#include folder
INCLUDE_SRC = kernel/include
#kernel folder
KERNEL_SRC = kernel
#boot folder
BOOT_SRC = $(KERNEL_SRC)/boot
#src folder
SRC = $(KERNEL_SRC)/src
#build folder
BUILD = build
#kernel obj folder
KERNEL_OBJ = $(BUILD)/$(KERNEL_SRC)
#boot obj folder
BOOT_OBJ = $(BUILD)/$(BOOT_SRC)
#src files
SRC_OBJ = $(BUILD)/$(SRC)
#io obj folder

#gcc flags
CC_FLAGS = -Wall -Wextra -ffreestanding -mcpu=cortex-a53 -mgeneral-regs-only -I $(INCLUDE_SRC)
#assembler flags
AS_FLAGS =
#linker flags
LD_FLAGS = -nostdlib
#qemu flags
QM_FLAGS = -machine raspi3b -kernel $(KERNEL_OBJ)/$(KERNEL_ELF) -serial null -serial stdio
#gdb flags
GDB_FLAGS = $(KERNEL_OBJ)/$(KERNEL_ELF) -ex "target remote localhost:1234" -ex "lay split" -ex "set scheduler-locking step"

#linker file
LINKER = $(KERNEL_SRC)/linker.ld
#object files
OBJ =	$(KERNEL_OBJ)/kernel.o\
	$(SRC_OBJ)/memory.o\
	$(SRC_OBJ)/debug.o\
	$(SRC_OBJ)/string.o\
	$(SRC_OBJ)/uart1.o\

$(KERNEL_ELF): $(OBJ) $(BOOT_OBJ)/boot.o
	@printf "LD $(KERNEL_OBJ)/$(KERNEL_ELF)\n"
	@$(LD) $(LD_FLAGS) $(OBJ) $(BOOT_OBJ)/boot.o -T $(LINKER) -o $(KERNEL_OBJ)/$(KERNEL_ELF)

$(KERNEL_IMG): $(KERNEL_ELF)
	@printf "OC $(KERNEL_OBJ)/$(KERNEL_IMG)\n"
	@$(OBJCP) -O binary $(KERNEL_OBJ)/$(KERNEL_ELF) $(KERNEL_OBJ)/$(KERNEL_IMG)

install: $(KERNEL_IMG)
	@mkdir -p boot
	@sudo mount /dev/sda1 boot
	@sudo cp  $(KERNEL_OBJ)/$(KERNEL_IMG) boot/$(KERNEL_IMG)
	@sudo umount boot
	@printf "INSTALLED"

qemu: $(KERNEL_ELF)
	$(QEMU) $(QM_FLAGS)

gdb: $(KERNEL_ELF)
	$(QEMU) -s -S $(QM_FLAGS) & gdb $(GDB_FLAGS)
	-$(KILL)
	@printf "TERMINATED"

objd:
	@$(OBJDU) -D -s $(KERNEL_OBJ)/$(KERNEL_ELF) | less

kill:
	-$(KILL)
	@printf "TERMINATED"

img:
	@bash scripts/img.sh

clean:
	@yes | rm -f -r build/
	@mkdir build
	@mkdir build/kernel
	@mkdir build/kernel/boot
	@mkdir build/kernel/src
	@mkdir build/kernel/src/io

$(BOOT_OBJ)/boot.o : $(BOOT_SRC)/boot.S
	@printf "AS $(BOOT_SRC)/boot.S\n"
	@$(AS) $(AS_FLAGS) -c $(BOOT_SRC)/boot.S -o $(BOOT_OBJ)/boot.o

$(KERNEL_OBJ)/kernel.o : $(KERNEL_SRC)/kernel.c
	@printf "CC $(KERNEL_SRC)/kernel.c\n"
	@$(CC) $(CC_FLAGS) -o $(KERNEL_OBJ)/kernel.o -c $(KERNEL_SRC)/kernel.c

$(SRC_OBJ)/memory.o : $(SRC)/memory.c
	@printf "CC $(SRC)/memory.c\n"
	@$(CC) $(CC_FLAGS) -o $(SRC_OBJ)/memory.o -c $(SRC)/memory.c

$(SRC_OBJ)/debug.o : $(SRC)/debug.S	
	@printf "AS $(SRC)/debug.S\n"
	@$(AS) $(AS_FLAGS) -o $(SRC_OBJ)/debug.o $(SRC)/debug.S

$(SRC_OBJ)/string.o : $(SRC)/string.c
	@printf "CC $(SRC)/string.c\n"
	@$(CC) $(CC_FLAGS) -o $(SRC_OBJ)/string.o -c $(SRC)/string.c

$(SRC_OBJ)/uart1.o : $(SRC)/uart1.c
	@printf "CC $(SRC)/uart1.c\n"
	@$(CC) $(CC_FLAGS) -o $(SRC_OBJ)/uart1.o -c $(SRC)/uart1.c


$(SRC_OBJ)/gpio.o : $(SRC)/gpio.c
	@printf "CC $(SRC)/gpio.c\n"
	@$(CC) $(CC_FLAGS) -o $(SRC_OBJ)/gpio.o -c $(SRC)/gpio.c
