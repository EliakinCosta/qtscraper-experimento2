#!/bin/bash

export BASE_DIR=/data/teste-livro/
export ANDROID_NDK=$BASE_DIR/android-ndk-r20
export ANDROID_SDK_ROOT=$BASE_DIR/android-sdk-4333796
export Qt5_android=$BASE_DIR/Qt/5.13.2/android_arm64_v8a
export PATH=$ANDROID_SDK_ROOT/platform-tools/:$PATH
export ANT=/usr/bin/ant
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk/
export INSTALL_DIR=/data/devel/sei-mobile/usr
export CMAKE_SYSROOT=$ANDROID_NDK/platforms/android-21/arch-arm64/

git submodule init
git submodule update

cd tidy-html5
git apply ../tidy-patch.001

mkdir cmake-build
cd cmake-build

# Build for Android 64bit
cmake ../ -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} -DCMAKE_SYSROOT=$ANDROID_NDK/platforms/android-21/arch-arm64 -DCMAKE_ANDROID_API=21 -DANDROID_PLATFORM=21 -DANDROID_ABI=arm64-v8a
make -j 4 tidy-share
mv libtidy.so ../../libs/arm64-v8a/

# Build for Android 32bit
rm -rf *
cmake ../ -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} -DCMAKE_SYSROOT=$ANDROID_NDK/platforms/android-21/arch-arm -DCMAKE_ANDROID_API=21 -DANDROID_PLATFORM=21 -DANDROID_ABI=armeabi-v7a
make -j 4 tidy-share
mv libtidy.so ../../libs/armeabi-v7a/

cd ..
git checkout -- include/tidy.h
git clean -dfx
cd ..
rm -rf tidy-html5/cmake-build
