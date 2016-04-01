#~/bin/sh

COMP_PATH=/home/z80/projects/stm32f429-linux/arm-2010q1/bin
PATH=$COMP_PATH:$PATH

make $PARS defconfig  ARCH=arm CROSS_COMPILE=$COMP_PATH/arm-uclinuxeabi- O=../out/busybox-1.22.1
make $PARS menuconfig ARCH=arm CROSS_COMPILE=$COMP_PATH/arm-uclinuxeabi- O=../out/busybox-1.22.1



