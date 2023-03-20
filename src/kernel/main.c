#include "system.h"
#include "stdio.h"
#include "log.h"

#define VERSION "0.20.23.3"

void _kernel_panic(char *err)
{
    VGA_init();
    VGA_clear(0x41);
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t  KERNEL PANIC!! (O-O)\n\t\t\t\t%s", err);
    Log_critical("Panic", "A kernel panic occured, Reason: %s", err);
    for (;;);
}

void _test()
{
    VGA_init();
    printf("Hello from Druid OS\n");
    printf("Druid os version: %s", VERSION);
    printf("\n\nDruid ->");
    setLogLevel(log_debug);
    Log_debug("Main","This is a debug msg");
    Log_info("Main", "This is aa info msg");
    Log_warning("Main", "This is a warning msg");
    Log_error("Main", "This is an error msg");
    Log_critical("Main", "This is a critical msg");
}

void _start() {
    _test();
 //   _kernel_panic("Just to test this screen");  // uncomment to test kernel panic screen
    for (;;);
}
