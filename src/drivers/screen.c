#include "screen.h"

void VGA_set_cursor(uint32_t offset)
{
  offset /= 2;
  x86_write_port_byte(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
  x86_write_port_byte(VGA_DATA_REGISTER, (uint8_t) (offset >> 8));
  x86_write_port_byte(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
  x86_write_port_byte(VGA_DATA_REGISTER, (uint8_t) (offset & 0xff));
}

uint32_t VGA_get_cursor()
{
  x86_write_port_byte(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
  uint32_t offset = x86_read_port_byte(VGA_DATA_REGISTER) << 8;
  x86_write_port_byte(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
  offset += x86_read_port_byte(VGA_DATA_REGISTER);
  return offset * 2;
}

void SCREEN_clear(uint8_t color)
{
  if (!color)
    color = VGA_DEFAULT_COLOR;
  uint16_t empty = (color << 8);

  memsetw((uint16_t *)VGA_VIDEO_MEMORY, empty, 80 * 25);
}

void SCREEN_print_char_at(char character, int col, int row, uint8_t attribute)
{

  // If attribute is 0
  if (!attribute)
  {
    attribute = VGA_DEFAULT_COLOR;
  }

  uint32_t offset = (row * SCREEN_MAX_COLS) + col;
  VGA_set_cursor(offset);
  SCREEN_print_char(character, attribute);
}

void SCREEN_print_char(char character, uint8_t attribute)
{
  if (!attribute)
  {
    attribute = VGA_DEFAULT_COLOR;
  }

  uint32_t offset = VGA_get_cursor();
  if (offset > 2080) // Greater than VGA memory
  {
    VGA_set_cursor(0);
  }
  memset((char *)(VGA_VIDEO_MEMORY + offset), character, 1);
  memset((char *)(VGA_VIDEO_MEMORY + offset + 1), attribute, 1);
  VGA_set_cursor(offset + 2);
}

void SCREEN_print_string(char *string, uint8_t attribute)
{
  for (uint32_t i = 0; string[i] != '\0'; i++)
  {
    SCREEN_print_char(string[i], attribute);
  }
}

void SCREEN_print_string_at(char *string, int col, int row, uint8_t attribute)
{
  uint32_t offset = (row * SCREEN_MAX_COLS) + col;
  VGA_set_cursor(offset);
  for (uint32_t i = 0; string[i] != '\0'; i++)
  {
    SCREEN_print_char(string[i], attribute);
  }
}

void VGA_init()
{
  VGA_set_cursor(0);
}
