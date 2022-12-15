#pragma once
#include <stdint.h>
#include "system.h"

char *itoa(int num);

// Converts an unsigned integer to a string
char *utoa(uint32_t num);
void reverse(char *string);