#include "log.h"

static void writer_stderr(const char *color, const char *prefix, const char *fmt, va_list args)
{
    fprintf(stderr, "%s%s%s ", color, prefix, RESET);
    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
}

void log_success(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    writer_stderr(GREEN, "[+]", fmt, args);

    va_end(args);
}

void log_error(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    writer_stderr(RED, "[-]", fmt, args);

    va_end(args);
}

void log_debug(const char *fmt, ...)
{
#if DEBUG
    va_list args;
    va_start(args, fmt);

    writer_stderr(CYAN, "[D]", fmt, args);

    va_end(args);
#endif
}

void log_warn(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    writer_stderr(YELLOW, "[!]", fmt, args);

    va_end(args);
}

void log_info(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    writer_stderr(BLUE, "[+]", fmt, args);

    va_end(args);
}