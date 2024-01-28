#!/bin/bash

#check if booloader is compiled
if [ -f cache/u-boot/u-boot-sunxi-with-spl.bin ]; then

    #check fi the device is set
    if ! [ "$DEVICE" == "" ]; then
        dd if=/dev/zero of=$DEVICE bs=1M count=8
        printf "o\nn\np\n\n\n\nw\n" | fdisk $DEVICE
        mkfs.ext4 ${DEVICE}1
        dd if=$UBOOTBIN_PATH of=${DEVICE} bs=1024 seek=8
    else
        printf "\033[1;91merror: no specified DEVICE"
    fi
else
    printf "\033[1;91merror: bootloader binary not found."
fi
