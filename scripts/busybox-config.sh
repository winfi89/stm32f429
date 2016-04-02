#~/bin/sh

ROOT_DIR=$PWD

busybox_src=$ROOT_DIR/../busybox-1.22.1
busybox_build=$ROOT_DIR/../out/busybox
busybox_romfs=$ROOT_DIR/../out/romfs
mkdir -p $busybox_build
mkdir -p $busybox_romfs
cp    -f $ROOT_DIR/../scripts/busybox_config $busybox_build/.config
#exit 0

TOOLCHAIN_PATH=/home/z80/projects/stm32f429-linux/arm-2010q1
BIN_PATH=$TOOLCHAIN_PATH/bin
INC_PATH=$TOOLCHAIN_PATH/arm-uclinuxeabi/libc/usr/include
LIB_PATH=$TOOLCHAIN_PATH/arm-uclinuxeabi/libc/usr/lib
CROSS_COMPILE=$TOOLCHAIN_PATH/arm-uclinuxeabi-
#export PATH=$COMP_PATH:$INC_PATH:$LIB_PATH:$BASE_PATH/libc/usr:$PATH

make -C $busybox_src O=$busybox_build oldconfig
