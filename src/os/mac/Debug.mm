#include "os/Debug.hpp"
#include <cstdio>
#include <cstdarg>

void OsOutputDebugString(const char* format, ...) {
    // TODO
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    return;
}
