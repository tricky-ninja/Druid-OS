#pragma once

#include "../drivers/screen.h"
#include <stdarg.h>

enum
{
  NORMAL_STATE,
  SPECIFIER_STATE,
};

int putc(char ch);
int puts(char *string);

void printf(char *format, ...);
char *numToString(uint32_t num);