#!/bin/bash

cpu_cores=$(nproc --all)

echo "------------------------Installing neccessary packages------------------------"
sudo apt install build-essential -y
sudo apt install bison -y
sudo apt install flex -y
sudo apt install libgmp3-dev -y
sudo apt install libmpc-dev -y
sudo apt install libmpfr-dev -y
sudo apt install texinfo -y

echo "------------------------Downloading gcc and binutils------------------------"
mkdir $HOME/Cross -p
rm $HOME/Cross -rf
cd $HOME/Cross

wget https://ftp.gnu.org/gnu/gcc/gcc-11.3.0/gcc-11.3.0.tar.gz
wget https://ftp.gnu.org/gnu/binutils/binutils-2.38.tar.gz

echo "------------------------Extracting gcc and binutils------------------------"
tar -xvf binutils-2.38.tar.gz
tar -xvf gcc-11.3.0.tar.gz

export PREFIX="$HOME/Cross/i686-elf"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

echo "------------------------Building binutils------------------------"
mkdir binutils-build
cd binutils-build/
../binutils-2.38/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j $cpu_cores
echo "------------------------Installing binutils------------------------"
make install

echo "------------------------Building gcc------------------------"
cd ..
mkdir gcc-build
cd gcc-build/
../gcc-11.3.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc -j $cpu_cores
make all-target-libgcc -j $cpu_cores

echo "------------------------Installing gcc------------------------"
make install-gcc -j $cpu_cores
make install-target-libgcc -j 2

echo "Done setting up 32 bit gcc try runniint it with $(TARGET)-gcc"