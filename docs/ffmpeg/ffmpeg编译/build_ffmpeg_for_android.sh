#!/bin/bash
ROOT_DIR=`pwd`/
echo $ROOT_DIR

#配置输出路径
PREFIX=$ROOT_DIR/android-build
if [[ ! -d "$PREFIX" ]]; then
    mkdir $PREFIX
fi

#设置你自己的NDK位置
NDK_HOME=/Users/junzhao/android/android-ndk-r14b
#设置你自己的平台，这上Mac上的，linux换成linux-x86_64
NDK_HOST_PLATFORM=darwin-x86_64
SYSROOT=$NDK_HOME/platforms/android-19/arch-arm/
SYSROOT64=$NDK_HOME/platforms/android-21/arch-arm64/
TOOLCHAIN_ARM7=$NDK_HOME/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64
TOOLCHAIN_ARM64=$NDK_HOME/toolchains/aarch64-linux-android-4.9/prebuilt/darwin-x86_64

COMMON_OPTIONS="\
    --enable-cross-compile \
    --target-os=linux \
    --disable-static \
    --enable-shared \
    --enable-small \
    --disable-programs \
    --disable-ffmpeg \
    --disable-ffplay \
    --disable-ffprobe \
    --disable-doc \
    --disable-symver \
    --disable-asm \
    --disable-linux-perf \
    "                   
function build_android {
    ./configure \
    --prefix=$PREFIX/armeabi-v7a \
    --arch=armeabi-v7a \
    --cross-prefix=$TOOLCHAIN_ARM7/bin/arm-linux-androideabi- \
    --sysroot=$SYSROOT \
    --extra-cflags="-Os -fpic $ADDI_CFLAGS" \
    --extra-ldflags="$ADDI_LDFLAGS" \
    $COMMON_OPTIONS
    make clean
    make -j8 && make install

    ./configure \
    --prefix=$PREFIX/aarch64 \
    --arch=aarch64 \
    --cpu=armv8-a \
    --cross-prefix=$TOOLCHAIN_ARM64/bin/aarch64-linux-android- \
    --sysroot=$SYSROOT64 \
    --extra-ldexeflags=-pie \
    ${COMMON_OPTIONS} 
    make clean
    make -j8 && make install

    ./configure \
    --prefix=$PREFIX/x86 \
    --arch=x86 \
    --cpu=i686 \
    --cross-prefix="${NDK_HOME}/toolchains/x86-4.9/prebuilt/${NDK_HOST_PLATFORM}/bin/i686-linux-android-" \
    --sysroot="${NDK_HOME}/platforms/android-19/arch-x86/" \
    --extra-ldexeflags=-pie \
    ${COMMON_OPTIONS} 
    make clean
    make -j8 && make install

    ./configure \
    --prefix=$PREFIX/x86_64 \
    --arch=x86_64 \
    --cpu=x86_64 \
    --cross-prefix="${NDK_HOME}/toolchains/x86_64-4.9/prebuilt/${NDK_HOST_PLATFORM}/bin/x86_64-linux-android-" \
    --sysroot="${NDK_HOME}/platforms/android-21/arch-x86_64/" \
    --extra-ldexeflags=-pie \
    ${COMMON_OPTIONS}
    make clean
    make -j8 && make install
};

build_android
