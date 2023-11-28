#include <stdarg.h>
#include <stdio.h>

void logger(const char* restrict format, ...){
    va_list arg;
    va_start(arg, format);
    vprintf(format, arg);
    va_end(arg);
}
