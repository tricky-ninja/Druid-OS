#pragma once

#include <stdint.h>

uint8_t i686_read_port_byte(uint16_t port);
void i686_write_port_byte(uint16_t port, uint8_t data);