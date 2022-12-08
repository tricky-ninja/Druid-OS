#pragma once

#include "x86.h"

/*
  Copies count bytes of memory from source to destination
  @params:
    dest - a pointer to the destination memory
    src - a pointer to the source memory
    count - number of bytes to be copied
  @returns:
    the starting address of the destination
*/
uint8_t *memcpy(uint8_t *dest, const uint8_t *src, uint32_t count);

/*
  Sets count bytes of memory in destination to the sepcifed value
  @params:
    dest - a pointer to the destination memory
    val - the value to be filled
    count - number of bytes to be copied
  @returns:
    the starting address of the destination
*/
uint8_t *memset(uint8_t *dest, uint8_t val, uint32_t count);

/*
  Sets count words(2 bytes) of memory in destination to the sepcifed value
  @params:
    dest - a pointer to the destination memory
    val - the value to be filled
    count - number of words to be copied
  @returns:
    the starting address of the destination
*/
uint16_t *memsetw(uint16_t *dest, uint16_t val, uint32_t count);

/*
  Calculates the length of a null terminated string
  @params:
    str - a pointer to the string
  @returns:
    the length of the string
*/
uint32_t strlen(const char *str);