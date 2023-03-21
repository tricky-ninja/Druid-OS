#pragma once

#include "arch/i686/vga.h"
#include <stdarg.h>
#include "utils/string.h"

#define putc(ch) putc_internal(false, (char)ch)
#define dbg_putc(ch) putc_internal(true, (char)ch)
#define puts(str) puts_internal(false, (char*)str)
#define dbg_puts(str) puts_internal(true, (char*)str)
#define printf(...) printf_internal(false, __VA_ARGS__)
#define dbg_printf(...) printf_helper(true, __VA_ARGS__)

enum PrintfState
{
  NORMAL_STATE,
  SPECIFIER_STATE,
};

int putc_internal(bool debug, char ch);
int puts_internal(bool debug, char *string);

//
// WARNING: There is a helper function that takes in a va_list and another function that takes variable args, 
// since logf can only pass a va_list to printf we need a printf that can accept va_lists this is a hacky solution
// 
void printf_internal(bool debug, char *format, ...);
void printf_helper(bool debug, char *format, va_list args);