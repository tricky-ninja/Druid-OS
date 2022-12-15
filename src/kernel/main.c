#include "system.h"
#include "stdio.h"

void _kernel_panic(char *err)
{
    VGA_init();
    VGA_clear(0x41);
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t  KERNEL PANIC!! (O-O)\n\t\t\t\t%s", err);
    for (;;);
}

void _test()
{
    VGA_init();
    printf("%c %s at your service in %d %u seconds", 'l', "Druid OS", -22, -22);
}

void _start() {
    _test();
    // _kernel_panic("Error description here");  // uncomment to test kernel panic screen
    for (;;);
}
