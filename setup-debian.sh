#!/bin/bash
read -p "Press any key to continue... " -n1 -s
sudo apt install build-essential nasm mtools qemu-system-x86 bochs bochs-sdl -y
bash ./cross-gcc-debian.sh