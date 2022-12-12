#include "stdio.h"

int putc(char ch)
{
  VGA_print_char(ch, 0);
  return ch;
}

int puts(char *string)
{
  for (uint32_t i = 0; i < strlen(string); i++)
  {
    VGA_print_char(string[i],0);
  }
  return strlen(string);
}