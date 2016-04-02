#~/bin/sh

ROOT_DIR=$PWD

ROOTFS_CFLAGS=-march=armv7-m -mtune=cortex-m4 \
-mlittle-endian -mthumb \
-Os -ffast-math \
-ffunction-sections -fdata-sections \
-Wl,--gc-sections \
-fno-common \
--param max-inline-insns-single=1000 \
-Wl,-elf2flt=-s -Wl,-elf2flt=16384


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
CROSS_COMPILE=$BIN_PATH/arm-uclinuxeabi-
#export PATH=$COMP_PATH:$INC_PATH:$LIB_PATH:$BASE_PATH/libc/usr:$PATH

# Build
make -C $busybox_build ARCH=arm CROSS_COMPILE=$CROSS_COMPILE CFLAGS=$ROOTFS_CFLAGS SKIP_STRIP=y CONFIG_PREFIX=$busybox_romfs
# Install
make -C $busybox_build ARCH=arm CROSS_COMPILE=$CROSS_COMPILE CFLAGS=$ROOTFS_CFLAGS SKIP_STRIP=y CONFIG_PREFIX=$busybox_romfs install

# make -C $(busybox_dir) \
#   O=$(target_out_busybox) oldconfig
# make -C $(target_out_busybox) \
#   ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) \
#   CFLAGS=$(ROOTFS_CFLAGS) SKIP_STRIP=y \
#   CONFIG_PREFIX=$(target_out_romfs) install
