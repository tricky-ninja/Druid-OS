#pragma once

#include <stdint.h>
#include "../kernel/system.h"

#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e
#define VGA_DEFAULT_COLOR 0x0f
#define VGA_VIDEO_MEMORY 0xb8000

#define SCREEN_MAX_ROWS 25
#define SCREEN_MAX_COLS 80

void VGA_set_cursor(uint32_t offset);
uint32_t VGA_get_cursor();

void SCREEN_print_char_at(char character, int col, int row, uint8_t attribute);
void SCREEN_print_char(char character, uint8_t attribute);

void SCREEN_print_string_at(char *string, int col, int row, uint8_t attribute);
void SCREEN_print_string(char *string, uint8_t attribute);
void SCREEN_clear(uint8_t color);

void VGA_init();