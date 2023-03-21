$(BUILD_DIR)/kernel.bin: $(BUILD_DIR)/kernel_entry.o ${OBJ_FILES}
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

$(BUILD_DIR)/kernel_entry.o: $(KENREL_DIR)/kernel_entry.asm create
	$(ASM) $< -f elf -o $@