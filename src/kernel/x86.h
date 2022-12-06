#pragma once

#include <stdint.h>

uint8_t x86_read_port_byte(uint16_t port);
void x86_write_port_byte(uint16_t port, uint8_t data);
uint16_t x86_read_port_word(uint16_t port);
void x86_write_port_word(uint16_t port, uint16_t data);
