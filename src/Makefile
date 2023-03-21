C_SOURCES=$(wildcard $(KENREL_DIR)/*.c $(DRIVER_DIR)/*.c) \
					$(wildcard $(KENREL_DIR)/*/*.c $(DRIVER_DIR)/*/*.c) \
					$(wildcard $(KENREL_DIR)/*/*/*.c $(DRIVER_DIR)/*/*/*.c) \
					$(wildcard $(KENREL_DIR)/*/*/*/*.c $(DRIVER_DIR)/*/*/*/*.c) \

# the ’.c’ extension of filenames in C_SOURCES with ’.o’
OBJ_FILES=$(patsubst src/%.c, $(BUILD_DIR)/%.o, $(C_SOURCES))

$(BUILD_DIR)/bootloader.bin: $(BOOT_DIR)/main.asm
	$(ASM) -f bin $< -o $@

# Generic rule for building ’somefile .o’ from ’somefile .c’
$(BUILD_DIR)/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/kernel.bin: $(BUILD_DIR)/kernel_entry.o ${OBJ_FILES}
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

$(BUILD_DIR)/kernel_entry.o: $(KENREL_DIR)/kernel_entry.asm
	$(ASM) $< -f elf -o $@

