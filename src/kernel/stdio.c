#include "stdio.h"

int putc_internal(bool debug,char ch)
{
  if (debug)  x86_write_port_byte(0xE9, ch);
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
  char *fmt = format;
  int state = NORMAL_STATE;
  va_list args;
  va_start(args, format);
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
          puts_internal(debug,utoa(value));
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
  va_end(args);
}
