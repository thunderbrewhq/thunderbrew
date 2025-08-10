#include "os/Debug.hpp"
#include <cstdarg>
#include <cstdio>
#include <windows.h>

void OsOutputDebugString(const char* format, ...) {
    char buffer[512];

    va_list args;
    va_start(args, format);

    vsnprintf(buffer, sizeof(buffer), format, args);
    OutputDebugString(buffer);
    return;
}
