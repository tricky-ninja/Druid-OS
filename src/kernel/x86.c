#include "x86.h"

uint8_t x86_read_port_byte(uint16_t port)
{
  uint8_t result;
  __asm__("in %%dx, %%al"
          : "=a"(result)
          : "d"(port));
  return result;
}

void x86_write_port_byte(uint16_t port, uint8_t data)
{
  __asm__("out %%al, %%dx"
          : : "a"(data)
          , "d"(port));
}
