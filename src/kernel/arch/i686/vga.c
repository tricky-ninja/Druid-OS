#include "vga.h"

void VGA_set_cursor(uint8_t csrX, uint8_t csrY)
{
  g_currentContext.csrX = csrX;
  g_currentContext.csrY = csrY;

  if (g_currentContext.csrX >= g_currentContext.maxCols)
  {
    g_currentContext.csrX = 0;
    g_currentContext.csrY++;
  }
  if (g_currentContext.csrY >= g_currentContext.maxRows)
    VGA_scroll(1);

  uint32_t offset = csr_to_offset(g_currentContext.csrX, g_currentContext.csrY);
  offset /= 2;
  i686_write_port_byte(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
  i686_write_port_byte(VGA_DATA_REGISTER, (uint8_t)(offset >> 8));
  i686_write_port_byte(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
  i686_write_port_byte(VGA_DATA_REGISTER, (uint8_t)(offset & 0xff));
}

uint32_t VGA_get_cursor_offset()
{
  i686_write_port_byte(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
  uint32_t offset = i686_read_port_byte(VGA_DATA_REGISTER) << 8;
  i686_write_port_byte(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
  offset += i686_read_port_byte(VGA_DATA_REGISTER);
  return offset * 2;
}

void VGA_clear(uint8_t color)
{
  if (!color)
    color = g_currentContext.color;

  g_currentContext.color = color;

  uint16_t blank = 0x20 | (color << 8);

  memsetw((uint16_t *)g_currentContext.videoAddress, blank, g_currentContext.maxCols * g_currentContext.maxRows);
  VGA_set_cursor(0, 0);
}

void VGA_print_char_at(char character, int col, int row, uint8_t attribute)
{
  VGA_set_cursor(col, row);
  VGA_print_char(character, attribute);
}

void VGA_print_char(char character, uint8_t attribute)
{
  if (!attribute)
  {
    attribute = g_currentContext.color;
  }

  if (character == '\n')
  {
    g_currentContext.csrX = 0;
    g_currentContext.csrY++;
  }

  else if (character == '\r')
  {
    g_currentContext.csrX = 0;
  }
  else if (character == '\t')
  {
    g_currentContext.csrX = (g_currentContext.csrX + 8) & ~(8 - 1);
  }
  else if (character == '\b')
  {
   if (g_currentContext.csrX != 0) g_currentContext.csrX--;
   uint32_t offset = csr_to_offset(g_currentContext.csrX, g_currentContext.csrY);
   memset(g_currentContext.videoAddress + offset, VGA_BLANK, 1);
   memset(g_currentContext.videoAddress + offset + 1, attribute, 1);
  }

  /* Any character greater than or equal to space is printable */
  else if (character >= ' ')
  {
    uint32_t offset = csr_to_offset(g_currentContext.csrX, g_currentContext.csrY);
    memset(g_currentContext.videoAddress + offset, character, 1);
    memset(g_currentContext.videoAddress + offset + 1, attribute, 1);
    g_currentContext.csrX++;
  }
  VGA_set_cursor(g_currentContext.csrX, g_currentContext.csrY);
}

uint32_t VGA_scroll(uint8_t amt)
{
  uint32_t offset = (amt * g_currentContext.maxCols) * 2; // the memory offset where x=0, y=amt
  uint32_t count = (g_currentContext.maxRows - amt) * g_currentContext.maxCols; // the number of words(2bytes) from x=0, y=amt to max address
  memcpy(g_currentContext.videoAddress, g_currentContext.videoAddress + offset, count * 2); // copy every byte from x=0, y=amt to max addres amt*max_col offset back 
  VGA_set_cursor(g_currentContext.csrX, g_currentContext.csrY - amt);                  //  Move csrY back amt times so that its relatively in the same position it originally was
  memsetw((uint16_t *)(g_currentContext.videoAddress + count * 2), VGA_BLANK, amt * 80); // sets all rows from x=79, y=max_col-amt to the end of vga array as the blank character
  return VGA_get_cursor_offset();
}

void VGA_init()
{
  g_currentContext.color = VGA_DEFAULT_COLOR;
  VGA_set_cursor(0, 0);
  VGA_clear(VGA_DEFAULT_COLOR);
}

// Helper functions
uint32_t csr_to_offset(uint8_t col, uint8_t row)
{
  return 2 * (row * g_currentContext.maxCols + col);
}