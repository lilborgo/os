

#compiler
CC = aarch64-linux-gnu-gcc
#assembler
AS = aarch64-linux-gnu-as
#linker
LD = aarch64-linux-gnu-ld
#object copy
OBJCP = aarch64-linux-gnu-objcopy
#qemu binary
QEMU = qemu-system-aarch64
#kill qemu if exist
KILL = pkill -9 -f $(QEMU)


#include folder
INCLUDE_SRC = kernel/include
#kernel folder
KERNEL_SRC = kernel
#boot folder
BOOT_SRC = $(KERNEL_SRC)/boot
#src folder
SRC = $(KERNEL_SRC)/src
#io folder
IO_SRC = $(KERNEL_SRC)/src/io
#build folder
BUILD = build
#kernel obj folder
KERNEL_OBJ = $(BUILD)/$(KERNEL_SRC)
#boot obj folder
BOOT_OBJ = $(BUILD)/$(BOOT_SRC)
#src files
SRC_OBJ = $(BUILD)/$(SRC)
#io obj folder
IO_OBJ = $(BUILD)/$(IO_SRC)

#gcc flags
CC_FLAGS = -Wall -ffreestanding -nostdlib -nostdinc -mcpu=cortex-a72 -nostartfiles -mgeneral-regs-only -I $(INCLUDE_SRC) -g -ggdb
#assembler flags
AS_FLAGS = -g -gdb
#linker flags
LD_FLAGS = -nostdlib
#qemu flags
QM_FLAGS = -m 4G -machine virt -cpu cortex-a72 -kernel $(KERNEL_OBJ)/kernel.elf --nographic

#linker file
LINKER = $(KERNEL_SRC)/linker.ld
#object files
OBJ =	$(KERNEL_OBJ)/kernel.o\
	$(SRC_OBJ)/memory.o\
	$(IO_OBJ)/uart.o\
	$(SRC_OBJ)/debug.o\
	$(SRC_OBJ)/string.o\

kernel.elf: $(OBJ) $(BOOT_OBJ)/boot.o
	@printf "LD $(KERNEL_OBJ)/kernel.elf\n"
	@$(LD) $(LD_FLAGS) $(OBJ) $(BOOT_OBJ)/boot.o -T $(LINKER) -o $(KERNEL_OBJ)/kernel.elf

local.elf: $(OBJ)
	@printf "LD $(KERNEL_OBJ)/local.elf\n"
	@$(LD) $(LD_FLAGS) $(OBJ) -o $(KERNEL_OBJ)/local.elf

kernel8.img: kernel.elf
	@printf "OC $(KERNEL_OBJ)/kernel8.img\n"
	@$(OBJCP) -O binary $(KERNEL_OBJ)/kernel.elf $(KERNEL_OBJ)/kernel8.img

install: kernel8.img
	@mkdir -p boot
	@bash .config
	@sudo mount /dev/sda1 boot
	@sudo cp  $(KERNEL_OBJ)/kernel8.img boot/kernel8.img
	@sudo umount boot
	@printf "INSTALLED"

qemu: kernel.elf
	$(QEMU) -s -S $(QM_FLAGS)

gdb: kernel.elf
	$(QEMU) -s -S $(QM_FLAGS) & gdb $(KERNEL_OBJ)/kernel.elf -ex "target remote localhost:1234" -ex "lay next"
	-$(KILL)
	@printf "TERMINATED"

objd:
	@aarch64-linux-gnu-objdump -D -s $(KERNEL_OBJ)/kernel.elf | less

kill:
	-$(KILL)
	@printf "TERMINATED"

u-boot:
	@bash scripts/u-boot.sh

img: u-boot
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
	@$(AS) -o $(BOOT_OBJ)/boot.o $(BOOT_SRC)/boot.S

$(KERNEL_OBJ)/kernel.o : $(KERNEL_SRC)/kernel.c
	@printf "CC $(KERNEL_SRC)/kernel.c\n"
	@$(CC) $(CC_FLAGS) -o $(KERNEL_OBJ)/kernel.o -c $(KERNEL_SRC)/kernel.c

$(IO_OBJ)/uart.o : $(IO_SRC)/uart.c
	@printf "CC $(IO_SRC)/uart.c\n"
	@$(CC) $(CC_FLAGS) -o $(IO_OBJ)/uart.o -c $(IO_SRC)/uart.c

$(SRC_OBJ)/memory.o : $(SRC)/memory.c
	@printf "CC $(SRC)/memory.c\n"
	@$(CC) $(CC_FLAGS) -o $(SRC_OBJ)/memory.o -c $(SRC)/memory.c

$(SRC_OBJ)/debug.o : $(SRC)/debug.S	
	@printf "AS $(SRC)/debug.S\n"
	@$(AS) -o $(SRC_OBJ)/debug.o $(SRC)/debug.S

$(SRC_OBJ)/string.o : $(SRC)/string.c
	@printf "CC $(SRC)/string.c\n"
	@$(CC) $(CC_FLAGS) -o $(SRC_OBJ)/string.o -c $(SRC)/string.c
