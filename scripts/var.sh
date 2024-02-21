#!/bin/bas

#build output directory
BUILD_DIR="build/"
#prefix for log
PREFIX_LOG="\033[0;32mlog "
#prefix for error
PREFIX_ERR="\033[1;91merror: "
#reset colors
RESET="\033[0m\n"
#image file path
VRT_DISK="${BUILD_DIR}dev.img"

#bootcode.bin link
BOOTCODE_BIN="https://github.com/raspberrypi/firmware/raw/master/boot/bootcode.bin"
#start.elf link
START_ELF="https://github.com/raspberrypi/firmware/raw/master/boot/start.elf"
#fixup.dat link
FIXUP_DAT="https://github.com/raspberrypi/firmware/raw/master/boot/fixup.dat"
#dtb rpi link plus
RPI_DTB_PLUS="https://github.com/raspberrypi/firmware/raw/master/boot/bcm2710-rpi-3-b-plus.dtb"
#dtp rpi link
RPI_DTB="https://github.com/raspberrypi/firmware/raw/master/boot/bcm2710-rpi-3-b.dtb"
#directory to mount the sd boot
BOOT_MOUNT="/mnt/rpiboot"
