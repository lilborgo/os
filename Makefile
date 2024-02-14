

#compiler
CC = aarch64-linux-gnu-gcc
#assembler
AS = aarch64-linux-gnu-as
#linker
LD = aarch64-linux-gnu-ld
#object copy
OBJCP = aarch64-linux-gnu-objcopy

#kernel folder
KERNEL_SRC = kernel
#boot folder
BOOT_SRC = $(KERNEL_SRC)/boot
#build folder
BUILD = build
#kernel obj folder
KERNEL_OBJ = $(BUILD)/$(KERNEL_SRC)
#boot obj folder
BOOT_OBJ = $(BUILD)/$(BOOT_SRC)

#gcc flags
CC_FLAGS = -Wall -ffreestanding -nostdlib -nostdinc -mcpu=cortex-a53 
#assembler flags
AS_FLAGS = 
#linker flags
LD_FLAGS = -nostdlib

#linker file
LINKER = $(KERNEL_SRC)/linker.ld
#object files
OBJ =	$(BOOT_OBJ)/boot.o\
		$(KERNEL_OBJ)/kernel.o\

kernel.elf: $(OBJ)
	@printf "LD $(KERNEL_OBJ)/kernel.elf\n"
	@$(LD) $(LD_FLAGS) $(OBJ) -T $(LINKER) -o $(KERNEL_OBJ)/kernel.elf

kernel.img: kernel.elf
	$(OBJCP) -O binary $(KERNEL_OBJ)/kernel.elf $(KERNEL_OBJ)/kernel.img

qemu: kernel.elf
	qemu-system-aarch64 -s -S -m 512 -machine virt -cpu cortex-a53 -kernel $(KERNEL_OBJ)/kernel.elf -nographic

u-boot:
	@bash scripts/u-boot.sh

img: u-boot
	@bash scripts/img.sh

clean:
	@yes | rm -f -r build/
	@mkdir build
	@mkdir build/kernel
	@mkdir build/kernel/boot

$(BOOT_OBJ)/boot.o : $(BOOT_SRC)/boot.S
	@printf "AS $(BOOT_SRC)/boot.S\n"
	@$(AS) -o $(BOOT_OBJ)/boot.o $(BOOT_SRC)/boot.S

$(KERNEL_OBJ)/kernel.o : $(KERNEL_SRC)/kernel.c
	@printf "CC $(KERNEL_SRC)/kernel.c\n"
	@$(CC) $(CC_FLAGS) -o $(KERNEL_OBJ)/kernel.o -c $(KERNEL_SRC)/kernel.c
