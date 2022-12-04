#!/bin/bash
sudo apt install build-essential nasm mtools qemu-system-x86 bochs bochs-x -y
read -p "Press any key to continue, if you want to install a cross compiler(REQUIRED if you are intrested in developing this project, might take a while on OLDER SYSTEMS) or PRESS ctrl+c to cancel" -n1 -s
bash ./cross-gcc-debian.sh