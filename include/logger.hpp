#pragma once

#ifdef LOGGING
#include <stdio.h>
#include <stdarg.h>
#endif // LOGGING

static inline void log(const char *format, ...)
{
#ifdef LOGGING
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
#endif // LOGGING
}