#include "log.h"

static const char *const g_debug_colorCodes[] = {
    [log_debug] = "\033[2;37m",
    [log_info] = "\033[0;35m",
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
  va_start(args, module);
  if (level < g_currentLevel)
    return;
  dbg_puts(g_debug_colorCodes[level]);
  printf_internal(true, "[%s] ", module);
  dbg_printf(string, args);
  va_end(args);
  dbg_puts("\033[0m\n");
}
