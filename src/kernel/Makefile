$(BUILD_DIR)/kernel.bin: $(BUILD_DIR)/kernel-entry.o ${OBJ_FILES}
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

$(BUILD_DIR)/kernel-entry.o: $(KENREL_DIR)/kernel-entry.asm create
	$(ASM) $< -f elf -o $@