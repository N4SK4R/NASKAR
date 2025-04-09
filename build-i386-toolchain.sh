#!/bin/bash

set -e

# Install dependencies
sudo apt update
sudo apt install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo wget

# Create working directory
mkdir -p opt
cd opt

# Download sources
wget -c https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.xz
wget -c https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.xz
tar -xf binutils-2.42.tar.xz
tar -xf gcc-13.2.0.tar.xz

# Build and install binutils
mkdir -p build-binutils
cd build-binutils
../binutils-2.42/configure --target=i386-elf --prefix=/usr/local/i386-elf --disable-nls --disable-werror
make -j$(nproc)
sudo make install
cd ..

# Build and install gcc
mkdir -p build-gcc
cd build-gcc
../gcc-13.2.0/configure --target=i386-elf --prefix=/usr/local/i386-elf --disable-nls --enable-languages=c,c++ --without-headers
make -j$(nproc) all-gcc
make -j$(nproc) all-target-libgcc
sudo make install-gcc
sudo make install-target-libgcc
cd ..

cd ..
sudo rm -rf opt

echo "✅ i386-elf toolchain built and installed to /usr/local/i386-elf"

