
ROOTFS_CFLAGS := "-march=armv7-m -mtune=cortex-m4 \
-mlittle-endian -mthumb \
-Os -ffast-math \
-ffunction-sections -fdata-sections \
-Wl,--gc-sections \
-fno-common \
--param max-inline-insns-single=1000 \
-Wl,-elf2flt=-s -Wl,-elf2flt=16384"

TOOLCHAIN_PATH := "/home/z80/projects/stm32f429-linux/arm-2010q1"

GCC := "$(TOOLCHAIN_PATH)/bin/arm-uclinuxeabi-gcc"

main:
	$(GCC) -static src/main.c -o main

all:
	main

clean:
	rm -rf main main.gdb

help:
	@echo "GTFO!"
