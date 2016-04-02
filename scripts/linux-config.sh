#~/bin/sh
cd ../linux-4.4.5
ARCH=arm
CROSS_COMPILE=/home/z80/programs/sw4stm32/plugins/fr.ac6.mcu.externaltools.arm-none.linux32_1.7.0.201602151102/tools/compiler/bin/arm-none-eabi-
#HOME=$PWD
#export ARCH
#export CROSS_COMPILE
#echo $ARCH
make menuconfig O=../out/linux-4.4.5
#PATH=$PATH:$PWD/openocd/bin:/$PWD/openocd/share/openocd/scripts:/home/z80/projects/stm32-kernel/linux-4.4.5/openocd/share/openocd/scripts/board
#openocd --file ./stm32f429discovery.cfg
#PATH=$PATH:/home/z80/programs/sw4stm32/plugins/fr.ac6.mcu.externaltools.arm-none.linux32_1.7.0.201602151102/tools/compiler/bin
#arm-none-eabi-gdb-py ./vmlinux -tui

