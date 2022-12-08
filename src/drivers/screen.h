#pragma once

#include <stdint.h>
#include "../kernel/system.h"

#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e
#define VGA_DEFAULT_COLOR 0xf0
#define VGA_VIDEO_MEMORY 0xb8000

#define SCREEN_MAX_ROWS 25
#define SCREEN_MAX_COLS 80

/*
  Sets the vga cursor position
  @params:
    offset - the offset in the vga array where the cursor needs to be
*/
void VGA_set_cursor(uint32_t offset);
uint32_t VGA_get_cursor();

/*
  Prints a charcater at a specific row and column of the screen and moves the cursor there
  @params:
    character - the ascii character to be printed
    col - the column where the character needs to be printed
    row - the row where the character needs to be printed
    attribute - the background and foreground color information
*/
void VGA_print_char_at(char character, int col, int row, uint8_t attribute);

/*
  Prints a charcater at the cursor location
  @params:
    character - the ascii character to be printed
    attribute - the background and foreground color information
*/
void VGA_print_char(char character, uint8_t attribute);

/*
  Prints a string at a specific row and column of the screen and moves the cursor there
  @params:
    string - a char pointer to the null terminated string that needs to be printed
    col - the column where the character needs to be printed
    row - the row where the character needs to be printed
    attribute - the background and foreground color information
*/
void VGA_print_string_at(char *string, int col, int row, uint8_t attribute);

/*
  Prints a string at the cursor location
  @params:
    string - a char pointer to the null terminated string that needs to be printed
    attribute - the background and foreground color information
*/
void VGA_print_string(char *string, uint8_t attribute);
void VGA_clear(uint8_t color);

uint32_t VGA_scroll(uint8_t amt);

void VGA_init();

// Helper functions
uint32_t csr_to_offset(uint8_t col, uint8_t row);