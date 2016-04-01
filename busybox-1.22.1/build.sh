#~/bin/sh

busybox_src=$PWD
busybox_build=$busybox_src/../out/busybox
busybox_romfs=$busybox_src/../out/romfs
mkdir -p $busybox_build
mkdir -p $busybox_romfs
cp    -f $PWD/../scripts/busybox_config $busybox_build/.config
#exit 0

BASE_PATH=/home/z80/projects/stm32f429-linux/arm-2010q1
COMP_PATH=$BASE_PATH/bin
INC_PATH=$BASE_PATH/arm-uclinuxeabi/libc/usr/include
LIB_PATH=$BASE_PATH/arm-uclinuxeabi/libc/usr/lib
CROSS_COMPILE=arm-uclinuxeabi-
export PATH=$COMP_PATH:$INC_PATH:$LIB_PATH:$BASE_PATH/libc/usr:$PATH

make -C $busybox_src ARCH=arm CROSS_COMPILE=$CROSS_COMPILE O=$busybox_build oldconfig 
make -C $busybox_build ARCH=arm CROSS_COMPILE=$CROSS_COMPILE CONFIG_PREFIX=$busybox_romfs install

