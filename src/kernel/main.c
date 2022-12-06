#include "system.h"
#include "../drivers/screen.h"

void _test()
{
    VGA_init();
    SCREEN_clear(0xbc);
    SCREEN_print_string("Wow that was really cool", 0xb2);
    SCREEN_print_string_at("Druid works!!!", 1040, 0, 0xbc);
}

void _start() {
    _test();
    for (;;);
}