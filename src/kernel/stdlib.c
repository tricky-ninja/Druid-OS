#include "stdlib.h"

char *itoa(int num)
{
  char *buffer;
  uint32_t temp = num;
  int i = 0;

  if (num < 0)
    temp = -num;

  while (temp > 0)
  {
    buffer[i++] = '0' + (temp % 10);
    temp = temp / 10;
  }

  if (num < 0)
    buffer[i++] = '-';

  buffer[i] = '\0';
  reverse(buffer);
  return buffer;
};

char *utoa(uint32_t num)
{
  char *buffer;
  uint32_t temp = num;
  int i = 0;

  while (temp > 0)
  {
    buffer[i++] = '0' + (temp % 10);
    temp = temp / 10;
  }

  buffer[i] = '\0';
  reverse(buffer);
  return buffer;
};

void reverse(char *string)
{
  static int i = 0;
  static int l;
  static int temptemporary_var;
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