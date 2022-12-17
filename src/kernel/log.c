#include "log.h"

static const char *const g_debug_colorCodes[] = {
    [log_debug] = "\033[2;37m",
    [log_info] = "\033[36m",
    [log_warning] = "\033[1;93m",
    [log_error] = "\033[1;31m",
    [log_critical] = "\033[1;97;101m",
};

static LogLevel g_currentLevel = log_info;

void setLogLevel(LogLevel level)
{
  g_currentLevel = level;
}

void logf(LogLevel level, char *module, char *string, ...)
{
  va_list args;
  va_start(args, string);
  if (level < g_currentLevel)
    return;
  dbg_puts(g_debug_colorCodes[level]);
  dbg_printf("[%s] ", module);
  dbg_printf(string, args);
  dbg_puts("\033[0m\n");
  va_end(args);
}
