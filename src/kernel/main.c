#include "memory.h"
#include "stdio.h"
#include "log.h"

#define VERSION "0.20.23.3"

void _kernel_panic(char *err)
{
    VGA_clear(0x41);
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t  KERNEL PANIC!! (O-O)\n\t\t\t\t%s", err);
    Log_critical("Main", "A kernel panic occured, Reason: %s", err);
    for (;;);
}

void _start() {
    setLogLevel(log_info);
    Log_info("Main", "Kernel loaded!");
    VGA_init();
    Log_info("Main", "Intialized VGA");
    printf("Hello from Druid OS\n");
    printf("Druid os version: %s", VERSION);
    printf("\n\nDruid ->");
    // _kernel_panic("Just to test this screen"); // uncomment to test kernel panic screen
    for (;;);
}
