#pragma once

#include "x86.h"

uint8_t *memcpy(uint8_t *dest, const uint8_t *src, uint32_t count);
uint8_t *memset(uint8_t *dest, uint8_t val, uint32_t count);
uint16_t *memsetw(uint16_t *dest, uint16_t val, uint32_t count);
uint32_t strlen(const char *str);