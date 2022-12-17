#pragma once
#include <stdint.h>
#include "system.h"

typedef enum bool{
  false = 0,
  true = 1,
} bool;

char *itoa(int num);

// Converts an unsigned integer to a string
char *utoa(uint32_t num);
void reverse(char *string);
