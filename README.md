# Druid OS
## Overview
Druid OS is a hobby operating system that we are working on in our free time.
Our goal with Druid OS is to make it into a usable os with a functional shell, multi tasking user space programs and maybe a graphical shell...?(that maybe too far fetched)
## Building
Clone this repo with
```bash
git clone https://github.com/Xhackers7/Druid-OS.git
cd Druid-OS/
```
### Building dependencies
#### Debian or debian based(Ubuntu, Zorin, Mint, etc)
Setting up and building this project is fairly easy on debian, once in the project directory, run
```bash
chmod +x ./scripts/setup-debian.sh
./scripts/setup-debian.sh
```
When its done, you will have all the tools needed to test (and develop) this os depending on what you need
#### Arch or arch based
Building this on arch might need a little more effort, run the following command to install all the required packages
```bash
paru -S gcc make bison flex libgmp-static libmpc mpfr texinfo nasm mtools qemu-system-x86
```
**NOTE:** to install all the required packages on Arch, you need an [AUR helper](https://wiki.archlinux.org/title/AUR_helpers) (the one used here is paru).

The above commands will set everything needed to build this  project except a cross compiler, it is a lengthy process but all you need to do is edit `scripts/cross-gcc-debian.sh` to make it use pacman and change the package names as needed, [this page explains the process in detail](https://wiki.osdev.org/GCC_Cross-Compiler#Preparing_for_the_build).
### Running/Debugging
After all the necessary packages are installed you're ready to dive in, once you're in the project directory you can run the os with qemu emulator by running
```bash
make run
# or
make run_floppy
```
Debugging is done with BOCHS emulator and can be run by
```bash
make debug
```

## Features
### Current
- Simple bootloader, loads the kernel in memory and jumps to it
- Flat memory model
- VGA driver
- Basic Logging system (E9 hack)
### In development
- Basic standard library
- Keyboard driver
- Filesystem


