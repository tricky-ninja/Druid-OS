#include "stdio.h"

int putc_internal(bool debug,char ch)
{
  if (debug)  i686_write_port_byte(0xE9, ch); // E9 hack, works only in qemu and bochs
  else VGA_print_char(ch, 0);
  return ch;
}

int puts_internal(bool debug, char *string)
{
  for (uint32_t i = 0; i < strlen(string); i++)
  {
    putc_internal(debug, string[i]);
  }
  return strlen(string);
}

void printf_internal(bool debug, char *format, ...)
{
  va_list args;
  va_start(args, format);
  printf_helper(debug, format, args);
  va_end(args);
}

void printf_helper(bool debug, char *format, va_list args)
{
  char *fmt = format;
  int state = NORMAL_STATE;
  while (*fmt != '\0')
  {
    switch (state)
    {
    case NORMAL_STATE:
      if (*fmt == '%')
        state = SPECIFIER_STATE;
      else
        putc_internal(debug, *fmt);
      break;

    case SPECIFIER_STATE:
      switch (*fmt)
      {
      case 'i':
      case 'd':
      {
        int value = va_arg(args, int);
        puts_internal(debug, itoa(value));
      }
      break;

      case 'u':
      {
        uint32_t value = va_arg(args, int);
        puts_internal(debug, utoa(value));
      }
      break;

      case 's':
      {
        char *value = va_arg(args, char *);
        puts_internal(debug, value);
      }
      break;

      case 'c':
      {
        char value = (char)va_arg(args, int);
        putc_internal(debug, value);
      }
      break;

      default:
        break;
      }
      state = NORMAL_STATE;
      break;

    default:
      break;
    }
    fmt++;
  }
}