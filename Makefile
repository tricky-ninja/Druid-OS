BOOT_DIR = src/boot
KENREL_DIR = src/kernel
DRIVER_DIR = src/drivers
BUILD_DIR = bins

ASM = nasm
CC = i686-elf-gcc
LD = i686-elf-gcc

CFLAGS = -ffreestanding -nostdlib
LDFLAGS = -T $(KENREL_DIR)/link.ld -nostdlib

LIBS += -lgcc

include src/Makefile

.PHONY: all clean create run debug

all: $(BUILD_DIR)/disk.img

$(BUILD_DIR)/disk.img: $(BUILD_DIR)/bootloader.bin $(BUILD_DIR)/kernel.bin
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=$< of=$@ bs=512 conv=notrunc seek=0
	dd if=$(word 2,$^) of=$@ bs=512 conv=notrunc seek=1

create:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/kernel
	mkdir -p $(BUILD_DIR)/drivers

clean:
	rm -rf $(BUILD_DIR)/*

run: $(BUILD_DIR)/disk.img
	qemu-system-i386 -debugcon stdio -machine q35 -drive file=$<,format=raw

run_floppy: $(BUILD_DIR)/disk.img
	qemu-system-i386 -machine q35 -fda $<

debug: bochs_config $(BUILD_DIR)/disk.img
	bochs -f $<





