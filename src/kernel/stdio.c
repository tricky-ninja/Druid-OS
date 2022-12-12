#include "stdio.h"

void reverse(char *string)
{

  static int i, l, temptemporary_var;
  l = strlen(string);
  if (i < l / 2)
  {
    temptemporary_var = string[i];
    string[i] = string[l - i - 1];
    string[l - i - 1] = temptemporary_var;
    i++;
    reverse(string);
  }
}

char *numToString(uint32_t num)
{
  char *buffer;
  uint32_t temp = num;
  int i = 0;
  while (temp > 0)
  {
    buffer[i] = '0'+(temp%10);
    temp = temp/10;
    i++;
  }

  buffer[i] = '\0';
  reverse(buffer);
  return buffer;
};

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
      if (*fmt == '%') state = SPECIFIER_STATE;
      else putc(*fmt);
      break;
    
    case SPECIFIER_STATE:
      switch (*fmt)
      {
      case 'd':
        {
          int value = va_arg(args, int);
          puts(numToString(value));
        }
        break;
      case 's':
       { char *value = va_arg(args, char*);
        puts(value);}
        break;
      
      case 'c':
        {char value = va_arg(args, char);
        putc(value);}
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