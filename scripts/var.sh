
BUILD_DIR="build/"
PREFIX_LOG="\033[0;32mlog "
PREFIX_ERR="\033[1;91merror: "
RESET="\033[0m\n"
U_BOOT_GIT="https://github.com/u-boot/u-boot"
ATF_GIT="https://github.com/ARM-software/arm-trusted-firmware.git"
U_BOOT_DIR="${BUILD_DIR}u-boot"
ATF_DIR="${BUILD_DIR}arm-trusted-firmware"
UBOOTBIN_PATH="${BUILD_DIR}u-boot/u-boot-sunxi-with-spl.bin"
export CROSS_COMPILE=aarch64-linux-gnu-
export BOARD=orangepi_zero3
export SOC_PLAT=sun50i_h616
export BL31_PATH=build/arm-trusted-firmware/build/${SOC_PLAT}/debug/bl31.bin

