#!/bin/bash

source scripts/var.sh

#check if booloader is compiled
if [ -f ${UBOOTBIN_PATH} ]; then

    #check fi the device is set
    if ! [ "$DEVICE" == "" ]; then
        printf "${PREFIX_LOG}Delteing partition table. ${RESET}"
        dd if=/dev/zero of=$DEVICE bs=1M count=8
        printf "${PREFIX_LOG}Creating partition table. ${RESET}"
        printf "o\nn\np\n\n\n\nw\n" | fdisk $DEVICE
        printf "${PREFIX_LOG}Creating filesystem. ${RESET}"
        mkfs.ext4 ${DEVICE}1
        printf "${PREFIX_LOG}Installing u-boot. ${RESET}"
        dd if=$UBOOTBIN_PATH of=${DEVICE} bs=1024 seek=8
    else
        printf "${PREFIX_ERR}No specified DEVICE. ${RESET}"
    fi
else
    printf "${PREFIX_ERR}Bootloader binary not found. ${RESET}"
fi
