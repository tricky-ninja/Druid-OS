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

void VGA_clear(uint8_t color)
{
  if (!color)
    color = VGA_DEFAULT_COLOR;
  uint16_t empty = 0x20 | (color << 8);

  memsetw((uint16_t *)VGA_VIDEO_MEMORY, empty, 80 * 25);
}

void VGA_print_char_at(char character, int col, int row, uint8_t attribute)
{

  uint32_t offset = csr_to_offset(col, row);
  VGA_set_cursor(offset*2);
  VGA_print_char(character, attribute);
}

void VGA_print_char(char character, uint8_t attribute)
{
  if (!attribute)
  {
    attribute = VGA_DEFAULT_COLOR;
  }

  uint32_t offset = VGA_get_cursor();
  if (offset >= SCREEN_MAX_ROWS * SCREEN_MAX_COLS * 2) {
     offset = VGA_scroll(1);
  }


  /* Any character greater than or equal to space is printable */
  if (character >= ' ')
  {
     memset((char *)(VGA_VIDEO_MEMORY + offset), character, 1);
     memset((char *)(VGA_VIDEO_MEMORY + offset + 1), attribute, 1);
     offset=offset+2;
  }
  VGA_set_cursor(offset);
  
}

void VGA_print_string(char *string, uint8_t attribute)
{
  for (uint32_t i = 0; i < strlen(string); i++)
  {
    VGA_print_char(string[i], attribute);
  }
}

void VGA_print_string_at(char *string, int col, int row, uint8_t attribute)
{
  uint32_t offset = (row * SCREEN_MAX_COLS) + col;
  VGA_set_cursor(offset*2);
  VGA_print_string(string, attribute);
}

uint32_t VGA_scroll(uint8_t amt)
{
  uint16_t blank = 0x20 | (VGA_DEFAULT_COLOR << 8);
  uint32_t offset = (amt*SCREEN_MAX_COLS)*2;
  uint32_t count = (SCREEN_MAX_ROWS - amt) * 80;
  memcpy((uint8_t*) VGA_VIDEO_MEMORY, (uint8_t*)(VGA_VIDEO_MEMORY+offset), count*2);
  VGA_set_cursor(VGA_get_cursor() - offset);
  memsetw((uint16_t*)(VGA_VIDEO_MEMORY+count*2), blank, amt*80);
  return VGA_get_cursor();
}

void VGA_init()
{
  VGA_set_cursor(0);
}


// Helper functions
uint32_t csr_to_offset(uint8_t col, uint8_t row)
{
  return 2 * (row * SCREEN_MAX_COLS + col);
}