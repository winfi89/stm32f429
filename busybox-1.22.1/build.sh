#~/bin/sh

BASE_PATH=/home/z80/projects/stm32f429-linux/arm-2010q1
COMP_PATH=$BASE_PATH/bin
INC_PATH=$BASE_PATH/arm-uclinuxeabi/libc/usr/include
LIB_PATH=$BASE_PATH/arm-uclinuxeabi/libc/usr/lib
PATH=$COMP_PATH:$INC_PATH:$LIB_PATH:$BASE_PATH/libc/usr:$PATH

make ARCH=arm CROSS_COMPILE=$COMP_PATH/arm-uclinuxeabi- O=../out/busybox-1.22.1 
make ARCH=arm CROSS_COMPILE=$COMP_PATH/arm-uclinuxeabi- O=../out/busybox-1.22.1 install CONFIG_PREFIX=../out/busybox-install

