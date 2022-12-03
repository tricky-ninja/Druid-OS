ASM = nasm
CC = gcc
LNK = ld

BOOT_SRC = bootloader/main.asm
KENREL_SRC = kernel/main.c
BUILD_DIR = build

.PHONY: all clean create run debug

all: $(BUILD_DIR)/disk.img

$(BUILD_DIR)/kernel.bin: $(BUILD_DIR)/kernel-entry.o $(BUILD_DIR)/kernel.o
	$(LNK) -m elf_i386 -o $@ -Ttext 0x7f00 $^ --oformat binary

$(BUILD_DIR)/kernel-entry.o: kernel/kernel-entry.asm create
	$(ASM) $< -f elf -o $@

$(BUILD_DIR)/kernel.o: $(KENREL_SRC) create
	$(CC) -fno-pie -m32 -ffreestanding -c $< -o $@

$(BUILD_DIR)/disk.img: $(BUILD_DIR)/bootloader.bin $(BUILD_DIR)/kernel.bin
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=$< of=$@ bs=512 conv=notrunc seek=0
	dd if=$(word 2,$^) of=$@ bs=512 conv=notrunc seek=1

$(BUILD_DIR)/bootloader.bin: $(BOOT_SRC) create
	$(ASM) -f bin $< -o $@


create:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*

run: $(BUILD_DIR)/disk.img
	qemu-system-i386 -machine q35 -drive file=$<,format=raw

run_floppy: $(BUILD_DIR)/disk.img
	qemu-system-i386 -machine q35 -fda $<

debug: bochs_config $(BUILD_DIR)/disk.img
	bochs -f $<
