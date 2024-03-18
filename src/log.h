#ifndef LOG
#define LOG

#include <stdio.h>
#include <stdarg.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define RESET "\x1b[0m"

void log_success(const char *fmt, ...);

void log_error(const char *fmt, ...);

void log_debug(const char *fmt, ...);

void log_warn(const char *fmt, ...);

void log_info(const char *fmt, ...);

#endif /* LOG */