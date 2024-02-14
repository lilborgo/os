#!/bin/bash

source scripts/var.sh

if [ $BOARD == "orangepi_zero3" ]; then

    # clone the u-boot repository
    if ! [ -d ${U_BOOT_DIR} ]; then
        printf "${PREFIX_LOG}Downloading u-boot.${RESET}"
        git clone --depth=1 ${U_BOOT_GIT} ${U_BOOT_DIR}
    else
        printf "${PREFIX_LOG}Not downloading u-boot.${RESET}"
    fi

    # clone the ATF repository
    if ! [ -d ${ATF_DIR} ]; then
        printf "${PREFIX_LOG}Downloading ATF.${RESET}"
        git clone --depth=1 ${ATF_GIT} ${ATF_DIR}
    else
        printf "${PREFIX_LOG}Not downloading ATF.${RESET}"
    fi

    # compiling ATF
    if ! [ -f $BL31_PATH ]; then
        printf "${PREFIX_LOG}Building bl31.bin.${RESET}"
        cd ${ATF_DIR}
        make -j$(nproc) PLAT=$SOC_PLAT DEBUG=1 bl31
        cd ../../
    else
        printf "${PREFIX_LOG}Not building bl31.bin.${RESET}"
    fi

    # compiling u-boot
    if ! [ -f ${UBOOTBIN_PATH} ]; then
        printf "${PREFIX_LOG}Building u-boot.bin${RESET}"
        cd ${U_BOOT_DIR}

        if ! [ -f .config ]; then
            printf "${PREFIX_LOG}Create default config file.${RESET}"
            make -j$(nproc) ${BOARD}_defconfig
            make -j$(nproc) menuconfig
        fi

        make -j$(nproc) BL31=../../${BL31_PATH}
    else
        printf "${PREFIX_LOG}Not building bootloader${RESET}"
    fi

    printf "${PREFIX_LOG}Done u-boot.${RESET}"
fi
