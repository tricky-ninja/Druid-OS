#include "system.h"
#include "../drivers/screen.h"

void _kernel_panic(char *err)
{
    VGA_init();
    VGA_clear(0x44);
    VGA_print_string_at("KERNEL PANIC!! (O-O)", (79 / 2) - strlen("KERNEL PANIC!! (X_X)") / 2, 11, 0x41);
    VGA_print_string_at(err, (79 / 2) - strlen(err) / 2, 12, 0x41);
    for (;;);
}

void _test()
{
    VGA_init();
    for (uint8_t i=0; i<26; i++)
    {
        VGA_print_char('\n', 0);
        VGA_print_char('a'+i, 0);
    }

}

void _start() {
    _test();
    // _kernel_panic("Error description here");  // uncomment to test kernel panic screen
    for (;;);
}
