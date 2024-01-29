#!/bin/bash

source scripts/var.sh

#check if its run with super user
if [[ $UID != 0 ]]; then
    printf "${PREFIX_ERR}Please run this with sudo.${RESET}"
    exit 1
fi

#create virtual disk file
if [ "$TYPE" == "img" ]; then
    printf "${PREFIX_LOG}Creating a virtual image(dev.img).${RESET}"
    rm -f $VRT_DISK
    dd if=/dev/zero of=$VRT_DISK bs=1M count=1024
    DEVICE=$VRT_DISK
else
    ROOT_PART="${DEVICE}1"
fi

#check if booloader is compiled
if [ -f ${UBOOTBIN_PATH} ]; then

    #check fi the device is set
    if ! [ "$DEVICE" == "" ]; then
        printf "${PREFIX_LOG}Delteing partition table. ${RESET}"
        dd if=/dev/zero of=$DEVICE bs=1M count=8
        printf "${PREFIX_LOG}Creating partition table. ${RESET}"
        printf "o\nn\np\n\n\n\nw\n" | fdisk $DEVICE
        printf "${PREFIX_LOG}Creating filesystem. ${RESET}"

        #associate disk file to loop device
        if [ "$TYPE" == "img" ]; then
            DEVICE=$(losetup -Pf --show $VRT_DISK)
            ROOT_PART="${DEVICE}p1"
            printf "${PREFIX_LOG}Using ${DEVICE}.${RESET}"
        fi

        #create filesystem
        mkfs.ext4 $ROOT_PART

        if [ "$TYPE" == "img" ]; then
            printf "${PREFIX_LOG}Deleting ${DEVICE}.${RESET}"
            losetup -d $DEVICE
            DEVICE=$VRT_DISK
        fi

        printf "${PREFIX_LOG}Installing u-boot. ${RESET}"
        dd if=$UBOOTBIN_PATH of=${DEVICE} bs=1024 seek=8
    else
        printf "${PREFIX_ERR}No specified DEVICE. ${RESET}"
    fi
else
    printf "${PREFIX_ERR}Bootloader binary not found. ${RESET}"
fi

