C_SOURCES=$(wildcard $(KENREL_DIR)/*.c $(DRIVER_DIR)/*.c) \
					$(wildcard $(KENREL_DIR)/*/*.c $(DRIVER_DIR)/*/*.c) \
					$(wildcard $(KENREL_DIR)/*/*/*.c $(DRIVER_DIR)/*/*/*.c) \
					$(wildcard $(KENREL_DIR)/*/*/*/*.c $(DRIVER_DIR)/*/*/*/*.c) \

# the ’.c’ extension of filenames in C_SOURCES with ’.o’
OBJ_FILES=$(patsubst src/%.c, $(BUILD_DIR)/%.o, $(C_SOURCES))

include $(KENREL_DIR)/Makefile
include $(BOOT_DIR)/Makefile

# Generic rule for building ’somefile .o’ from ’somefile .c’
$(BUILD_DIR)/%.o: src/%.c create
	$(CC) $(CFLAGS) -c $< -o $@