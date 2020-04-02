#!/bin/bash  
# 配置NDK路径
NDK=/Users/junzhao/android/android-ndk-r14b
# 指定了交叉编译环境,使其在编译过程中能够引用到 NDK 提供的原生标头和共享库文件
SYSROOT=$NDK/platforms/android-19/arch-arm/
TOOLCHAIN=$NDK/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64
#COMMON_FF_CFG_FLAGS="$COMMON_FF_CFG_FLAGS --disable-linux-perf"

# darwin linux
function build_one {
./configure \
--prefix=$PREFIX \
--enable-shared \
--disable-static \
--disable-doc \
--disable-ffmpeg \
--disable-ffplay \
--disable-ffprobe \
--disable-avdevice \
--disable-symver \
--disable-linux-perf \
--cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi- \
--target-os=linux \
--arch=armeabi-v7a \
--enable-cross-compile \
--sysroot=$SYSROOT \
--extra-cflags="-Os -fpic $ADDI_CFLAGS" \
--extra-ldflags="$ADDI_LDFLAGS" \
$ADDITIONAL_CONFIGURE_FLAG
make clean
make -j8
make install
}
CPU=armeabi-v7a
PREFIX=$(pwd)/android_build/$CPU
ADDI_CFLAGS="-marm"
build_one