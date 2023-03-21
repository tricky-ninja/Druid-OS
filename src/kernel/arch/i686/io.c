#include "io.h"

uint8_t i686_read_port_byte(uint16_t port)
{
  uint8_t result;
  __asm__("in %%dx, %%al"
          : "=a"(result)
          : "d"(port));
  return result;
}

void i686_write_port_byte(uint16_t port, uint8_t data)
{
  __asm__("out %%al, %%dx"
          : : "a"(data)
          , "d"(port));
}
