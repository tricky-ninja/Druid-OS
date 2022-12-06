ASM = nasm
C = i686-elf-gcc
LNK = i686-elf-ld

CFLAGS = -ffreestanding

BOOT_DIR = src/boot
KENREL_DIR = src/kernel
DRIVER_DIR = src/drivers
BUILD_DIR = build

# Automatically expand to a list of existing files that
# match the patterns
C_SOURCES=$(wildcard $(KENREL_DIR)/*.c $(DRIVER_DIR)/*.c)

# the ’.c’ extension of filenames in C_SOURCES with ’.o’
OBJ_FILES=$(patsubst src/%.c, $(BUILD_DIR)/%.o, $(C_SOURCES))

.PHONY: all clean create run debug

all: $(BUILD_DIR)/disk.img

$(BUILD_DIR)/kernel.bin: $(BUILD_DIR)/kernel-entry.o ${OBJ_FILES}
	$(LNK) -o $@ -Ttext 0x7f00 $^ --oformat binary

$(BUILD_DIR)/kernel-entry.o: $(KENREL_DIR)/kernel-entry.asm create
	$(ASM) $< -f elf -o $@

# Generic rule for building ’somefile .o’ from ’somefile .c’
$(BUILD_DIR)/%.o: src/%.c
	$(C) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/disk.img: $(BUILD_DIR)/bootloader.bin $(BUILD_DIR)/kernel.bin
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=$< of=$@ bs=512 conv=notrunc seek=0
	dd if=$(word 2,$^) of=$@ bs=512 conv=notrunc seek=1

$(BUILD_DIR)/bootloader.bin: $(BOOT_DIR)/main.asm create
	$(ASM) -f bin $< -o $@


create:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/kernel
	mkdir -p $(BUILD_DIR)/drivers

clean:
	rm -rf $(BUILD_DIR)/*

run: $(BUILD_DIR)/disk.img
	qemu-system-i386 -machine q35 -drive file=$<,format=raw

run_floppy: $(BUILD_DIR)/disk.img
	qemu-system-i386 -machine q35 -fda $<

debug: bochs_config $(BUILD_DIR)/disk.img
	bochs -f $<
