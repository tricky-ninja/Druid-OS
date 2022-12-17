#include "system.h"
#include "stdio.h"
#include "log.h"

void _kernel_panic(char *err)
{
    VGA_init();
    VGA_clear(0x41);
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t  KERNEL PANIC!! (O-O)\n\t\t\t\t%s", err);
    Log_critical("Panic", err);
    for (;;);
}

void _test()
{
    VGA_init();
    printf("%c %s at your service in %d or %u seconds", 'l', "Druid OS", -69, -69);
    setLogLevel(log_debug);
    Log_debug("Main","This is a debug msg");
    Log_info("Main", "This is aa info msg");
    Log_warning("Main", "This is a warning msg");
    Log_error("Main", "This is an error msg");
    Log_critical("Main", "This is a critical msg");
}

void _start() {
    _test();
    _kernel_panic("Error description here");  // uncomment to test kernel panic screen
    for (;;);
}
