#~/bin/sh
ARCH=arm
CROSS_COMPILE=/home/z80/projects/stm32f429-linux/arm-2010q1/bin/arm-uclinuxeabi-

PATH=$PATH:/home/z80/projects/stm32f429-linux/arm-2010q1/bin
arm-uclinuxeabi-gdb ../out/linux-4.4.5/vmlinux -tui

