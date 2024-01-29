#!/bin/bas

#build output directory
BUILD_DIR="build/"
#prefix for log
PREFIX_LOG="\033[0;32mlog "
#prefix for error
PREFIX_ERR="\033[1;91merror: "
#reset colors
RESET="\033[0m\n"
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
#image file path
VRT_DISK="${BUILD_DIR}dev.img"

#for compiling
export CROSS_COMPILE=aarch64-linux-gnu-
export BOARD=orangepi_zero3
export SOC_PLAT=sun50i_h616
export BL31_PATH=build/arm-trusted-firmware/build/${SOC_PLAT}/debug/bl31.bin

