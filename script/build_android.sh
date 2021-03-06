#!/bin/bash

git submodule update --init cmake/android-cmake

if [ -z "$ANDROID_NDK" ]; then
    echo "Did you set ANDROID_NDK variable?"
    exit 1
fi

if [ -d "$ANDROID_NDK" ]; then
    echo "Using Android ndk at $ANDROID_NDK"
else
    echo "Cannot find ndk: did you install it under $ANDROID_NDK?"
    exit 1
fi

if [ -z "$ANDROID_ABI" ]; then
    export ANDROID_ABI="armeabi-v7a with NEON"
    echo "Set ANDROID_ABI $ANDROID_ABI"
fi

mkdir -p build_android
cd build_android

cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=../cmake/android-cmake/android.toolchain.cmake \
    -DANDROID_NDK=$ANDROID_NDK \
    -DANDROID_ABI="$ANDROID_ABI" \
    -DCMAKE_BUILD_TYPE=Release \
    -DANDROID_NATIVE_API_LEVEL=21 \
    -DBUILD_TEST=ON \
    -DWITH_CUDA=OFF \
    $@ \
    || exit 1

# Cross-platform parallel build
if [ "$(uname)" = 'Darwin' ]; then
    cmake --build . -- "-j$(sysctl -n hw.ncpu)" || exit 1
else
    cmake --build . -- "-j$(nproc)" || exit 1
fi
