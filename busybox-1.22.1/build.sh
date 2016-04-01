#~/bin/sh
ARCH=arm
CROSS_COMPILE=CROSS_COMPILE=/home/z80/projects/stm32f429-linux/arm-2010q1/bin/arm-uclinux-
PATH=/home/z80/projects/stm32f429-linux/arm-2010q1/arm-uclinuxeabi/libc/usr/include:/home/z80/projects/stm32f429-linux/arm-2010q1/arm-uclinuxeabi/libc/usr/lib:$PATH

echo $PATH
#exit 0

#HOME=$PWD
#export ARCH
#export CROSS_COMPILE
#echo $ARCH

make
#make CONFIG_PREFIX=/home/z80/projects/stm32-kernel/busybox-install install


#PATH=$PATH:$PWD/openocd/bin:/$PWD/openocd/share/openocd/scripts:/home/z80/projects/stm32-kernel/linux-4.4.5/openocd/share/openocd/scripts/board
#openocd --file ./stm32f429discovery.cfg
#PATH=$PATH:/home/z80/programs/sw4stm32/plugins/fr.ac6.mcu.externaltools.arm-none.linux32_1.7.0.201602151102/tools/compiler/bin
#arm-none-eabi-gdb-py ./vmlinux -tui

