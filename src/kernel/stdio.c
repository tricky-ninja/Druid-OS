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
    VGA_print_char(string[i], 0);
  }
  return strlen(string);
}

void printf(char *format, ...)
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
        putc(*fmt);
      break;

    case SPECIFIER_STATE:
      switch (*fmt)
      {
      case 'i':
      case 'd':
      {
        int value = va_arg(args, int);
        puts(itoa(value));
      }
      break;

      case 'u':
        {
          uint32_t value = va_arg(args, int);
          puts(utoa(value));
        }
        break;

      case 's':
      {
        char *value = va_arg(args, char *);
        puts(value);
      }
      break;

      case 'c':
      {
        char value = (char)va_arg(args, int);
        putc(value);
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