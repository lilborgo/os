#!/bin/bash

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
    BOOT_PART="${DEVICE}1"
    ROOT_PART="${DEVICE}2"
fi

#check fi the device is set
if ! [ "$DEVICE" == "" ]; then
    printf "${PREFIX_LOG}Delteing partition table. ${RESET}"
    dd if=/dev/zero of=$DEVICE bs=1M count=8
    printf "${PREFIX_LOG}Creating partition table. ${RESET}"

    printf "o\nn\np\n\n\n+100M\na\nt\nc\nn\np\n\n\n\nw\n" | fdisk $DEVICE

    printf "${PREFIX_LOG}Creating filesystem. ${RESET}"

    #associate disk file to loop device
    if [ "$TYPE" == "img" ]; then
        DEVICE=$(losetup -Pf --show $VRT_DISK)
        BOOT_PART="${DEVICE}1"
        ROOT_PART="${DEVICE}2"
        printf "${PREFIX_LOG}Using ${DEVICE}.${RESET}"
    fi

    #create filesystem
    mkfs.vfat -F 32 -n boot $BOOT_PART
    mkfs.ext4 -F -L root $ROOT_PART

    if [ "$TYPE" == "img" ]; then
        printf "${PREFIX_LOG}Deleting ${DEVICE}.${RESET}"
        losetup -d $DEVICE
        DEVICE=$VRT_DISK
    fi

    #downloading raspi firmware
    mkdir $BOOT_MOUNT
    mount $BOOT_PART $BOOT_MOUNT
    wget $BOOTCODE_BIN -P $BOOT_MOUNT
    wget $START_ELF -P $BOOT_MOUNT
    wget $FIXUP_DAT -P $BOOT_MOUNT
    wget $RPI_DTB -P $BOOT_MOUNT
    wget $RPI_DTB_PLUS -P $BOOT_MOUNT
    cp config/config_rpi.txt $BOOT_MOUNT/config.txt
    umount $BOOT_MOUNT
    rm -r $BOOT_MOUNT

else
    printf "${PREFIX_ERR}No specified DEVICE. ${RESET}"
fi

