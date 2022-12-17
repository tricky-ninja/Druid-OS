#pragma once
#include "stdio.h"

#define Log_debug(module, ...) logf(log_debug, (char *)module, __VA_ARGS__)
#define Log_info(module, ...) logf(log_info, (char *)module, __VA_ARGS__)
#define Log_warning(module, ...) logf(log_warning, (char *)module, __VA_ARGS__)
#define Log_error(module, ...) logf(log_error, (char *)module, __VA_ARGS__)
#define Log_critical(module, ...) logf(log_critical, (char *)module, __VA_ARGS__)

typedef enum
{
  log_debug,
  log_info,
  log_warning,
  log_error,
  log_critical
} LogLevel;

void setLogLevel(LogLevel level);
void logf(LogLevel level, char *module, char *string, ...);