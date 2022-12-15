#pragma once

#include "../drivers/screen.h"
#include <stdarg.h>
#include "stdlib.h"

enum
{
  NORMAL_STATE,
  SPECIFIER_STATE,
};

int putc(char ch);
int puts(char *string);

void printf(char *format, ...);