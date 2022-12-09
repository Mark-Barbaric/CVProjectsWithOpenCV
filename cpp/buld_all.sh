#! /bin/sh

echo "build clean"

mkdir cmake-build
rm -rf cmake-build

echo "conan setup"

conan install . -pr conan_profiles/mac.profile -if cmake-build --build=missing

echo "generate and build"

cmake -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -B cmake-build -S .
make -C cmake-build/ -j ${NPROC}