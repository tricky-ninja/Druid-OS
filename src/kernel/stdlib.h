#pragma once
#include <stdint.h>
#include "memory.h"

typedef enum bool{
  false = 0,
  true = 1,
} bool;

char *itoa(int num);

// Converts an unsigned integer to a string
char *utoa(uint32_t num);
void reverse(char *string);

/*
  Calculates the length of a null terminated string
  @params:
    str - a pointer to the string
  @returns:
    the length of the string
*/
uint32_t strlen(const char *str);