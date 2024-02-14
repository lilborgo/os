#!/bin/bas

source .config

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

#orangepi_zero3 config

#u-boot repo
U_BOOT_GIT="https://github.com/u-boot/u-boot"
#arm-trusted-firmware repo
ATF_GIT="https://github.com/ARM-software/arm-trusted-firmware.git"
#u-boot directory
U_BOOT_DIR="${BUILD_DIR}u-boot"
#arm-trusted-firmware directory
ATF_DIR="${BUILD_DIR}arm-trusted-firmware"
#u-boot binary path
UBOOTBIN_PATH="${BUILD_DIR}u-boot/u-boot-sunxi-with-spl.bin"
#socket
export SOC_PLAT=sun50i_h616
#arm trusted firmware binary
export BL31_PATH=build/arm-trusted-firmware/build/${SOC_PLAT}/debug/bl31.bin

#rpi_4 config
#bootcode.bin link
BOOTCODE_BIN="https://github.com/raspberrypi/firmware/raw/master/boot/bootcode.bin"
#start4.elf link
START4_ELF="https://github.com/raspberrypi/firmware/raw/master/boot/start4.elf"
#fixup4.dat link
FIXUP4_DAT="https://github.com/raspberrypi/firmware/raw/master/boot/fixup4.dat"
#dtb rpi4 link
RPI4_DTB="https://github.com/raspberrypi/firmware/raw/master/boot/bcm2711-rpi-4-b.dtb"
#directory to mount the sd boot
BOOT_MOUNT="/mnt/rpiboot"

#for compiling
export CROSS_COMPILE=aarch64-linux-gnu-

