#!/bin/bash

export CROSS_COMPILE=aarch64-linux-gnu-
export BOARD=orangepi_zero3
export SOC_PLAT=sun50i_h616
export BL31_PATH=cache/arm-trusted-firmware/build/${SOC_PLAT}/debug/bl31.bin
export UBOOTBIN_PATH=u-boot/u-boot-sunxi-with-spl.bin

# clone the u-boot repository
if ! [ -d cache/u-boot/ ]; then
    printf "\033[0;32mlog: Downloading u-boot.\033[0m\n"
    git clone --depth=1 git://git.denx.de/u-boot.git cache/u-boot
else
    printf "\033[0;32mlog: Not downloading u-boot.\033[0m\n"
fi

# clone the ATF repository
if ! [ -d cache/arm-trusted-firmware/ ]; then
    printf "\033[0;32mlog: Downloading ATF.\033[0m\n"
    git clone --depth=1 https://github.com/ARM-software/arm-trusted-firmware.git cache/arm-trusted-firmware
else
    printf "\033[0;32mlog: Not downloading ATF.\033[0m\n"
fi

# compiling ATF

if ! [ -f $BL31_PATH ]; then
    printf "\033[0;32mlog: Building bl31.bin.\033[0m\n"
    cd cache/arm-trusted-firmware/
    make -j$(nproc) PLAT=$SOC_PLAT DEBUG=1 bl31
    cd ../../
else
    printf "\033[0;32mlog: Not building bl31.bin.\033[0m\n"
fi
##############

# compiling u-boot
if ! [ -f cache/u-boot/u-boot-sunxi-with-spl.bin ]; then
    printf "\033[0;32mlog: Building u-boot.bin\033[0m\n"
    cd cache/u-boot/

    if ! [ -f .config ]; then
        printf "\033[0;32mlog: Create default config file.\033[0m\n"
        make -j$(nproc) ${BOARD}_defconfig
        make -j$(nproc) menuconfig
    fi

    make -j$(nproc) BL31=../../${BL31_PATH}
else
    printf "\033[0;32mlog: Not building bootloader\033[0m\n"
fi
