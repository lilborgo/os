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

    if [ $BOARD == "orangepi_zero3" ]; then
        ROOT_PART="${DEVICE}1"
    elif [ $BOARD == "rpi_4" ]; then
        BOOT_PART="${DEVICE}1"
        ROOT_PART="${DEVICE}2"
    fi
fi


#check fi the device is set
if ! [ "$DEVICE" == "" ]; then
    printf "${PREFIX_LOG}Delteing partition table. ${RESET}"
    dd if=/dev/zero of=$DEVICE bs=1M count=8
    printf "${PREFIX_LOG}Creating partition table. ${RESET}"

    if [ $BOARD == "orangepi_zero3" ]; then
        printf "o\nn\np\n\n\n\nw\n" | fdisk $DEVICE
    elif [ $BOARD == "rpi_4" ]; then
        printf "o\nn\np\n\n\n+100M\na\nt\nc\nn\np\n\n\n\nw\n" | fdisk $DEVICE
    fi

    printf "${PREFIX_LOG}Creating filesystem. ${RESET}"

    #associate disk file to loop device
    if [ "$TYPE" == "img" ]; then
        DEVICE=$(losetup -Pf --show $VRT_DISK)

        if [ $BOARD == "orangepi_zero3" ]; then
            ROOT_PART="${DEVICE}1"
        elif [ $BOARD == "rpi_4" ]; then
            BOOT_PART="${DEVICE}1"
            ROOT_PART="${DEVICE}2"
        fi

        printf "${PREFIX_LOG}Using ${DEVICE}.${RESET}"
    fi

    if [ $BOARD == "orangepi_zero3" ]; then
        mkfs.ext4 $ROOT_PART
    elif [ $BOARD == "rpi_4" ]; then
        mkfs.vfat -F 32 -n boot $BOOT_PART
        mkfs.ext4 -F -L root $ROOT_PART
        sudo fatlabel $BOOT_PART
    fi

    #create filesystem


    if [ "$TYPE" == "img" ]; then
        printf "${PREFIX_LOG}Deleting ${DEVICE}.${RESET}"
        losetup -d $DEVICE
        DEVICE=$VRT_DISK
    fi

    if [ $BOARD == "orangepi_zero3" ]; then
        printf "${PREFIX_LOG}Installing u-boot. ${RESET}"
        dd if=$UBOOTBIN_PATH of=${DEVICE} bs=1024 seek=8
    elif [ $BOARD == "rpi_4" ]; then
        mkdir $BOOT_MOUNT
        mount $BOOT_PART $BOOT_MOUNT
        wget $START4_ELF -P $BOOT_MOUNT
        wget $FIXUP4_DAT -P $BOOT_MOUNT
        wget $RPI4_DTB -P $BOOT_MOUNT
        cp config/config_rpi.txt $BOOT_MOUNT/config.txt
        umount $BOOT_MOUNT
        rm -r $BOOT_MOUNT
    fi

else
    printf "${PREFIX_ERR}No specified DEVICE. ${RESET}"
fi

