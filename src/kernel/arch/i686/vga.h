#pragma once

#include <stdint.h>
#include "memory.h"

#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e
#define VGA_DEFAULT_COLOR 0xf0
#define VGA_BLANK (0x20 | (g_currentContext.color << 8))

typedef struct
{
  uint8_t *videoAddress;
  const uint8_t  maxRows;
  const uint8_t  maxCols;

  uint8_t  color; 
  uint8_t  csrX;
  uint8_t  csrY;

} VGA_Context;

static VGA_Context g_currentContext = {
    (uint8_t *)0xB8000,
    25,
    80,
    VGA_DEFAULT_COLOR,
    0,
    0,
};

/*
  Sets the vga cursor position
  @params:
    offset - the offset in the vga array where the cursor needs to be
*/
void VGA_set_cursor(uint8_t csrX, uint8_t csrY);
uint32_t VGA_get_cursor_offset();

/*
  Prints a charcater at a specific row and column of the screen and moves the cursor there
  @params:
    character - the ascii character to be printed
    col - the column where the character needs to be printed
    row - the row where the character needs to be printed
    color - the background and foreground color information
*/
void VGA_print_char_at(char character, int col, int row, uint8_t color);

/*
  Prints a charcater at the cursor location
  @params:
    character - the ascii character to be printed
    color - the background and foreground color information
*/
void VGA_print_char(char character, uint8_t color);

void VGA_clear(uint8_t color);

uint32_t VGA_scroll(uint8_t amt);

void VGA_init();

// Helper functions

uint32_t csr_to_offset(uint8_t col, uint8_t row);