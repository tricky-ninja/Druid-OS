#pragma once

#include "../drivers/screen.h"
#include <stdarg.h>
#include "stdlib.h"

#define putc(ch) putc_internal(false, (char)ch)
#define dbg_putc(ch) putc_internal(true, (char)ch)
#define puts(str) puts_internal(false, (char*)str)
#define dbg_puts(str) puts_internal(true, (char*)str)
#define printf(...) printf_internal(false, __VA_ARGS__)
#define dbg_printf(...) printf_internal(true, __VA_ARGS__)



enum PrintfState
{
  NORMAL_STATE,
  SPECIFIER_STATE,
};

int putc_internal(bool debug, char ch);
int puts_internal(bool debug, char *string);
void printf_internal(bool debug, char *format, ...);