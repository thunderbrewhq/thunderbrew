#include "util/CStatus.hpp"
#include "os/Debug.hpp"
#include <cstdarg>
#include <cstdio>

CStatus CStatus::s_errorList;

void CStatus::Add(const CStatus& source) {
    // TODO
    // Remove const_cast<> workaround
    CStatus& src = const_cast<CStatus&>(source);

    for (auto i = src.statusList.Head(); i; i = src.statusList.Next(i)) {
        this->Add(i->severity, i->text);
    }
}

void CStatus::Add(STATUS_TYPE severity, const char* format, ...) {
    // TODO
    // Remove temporary console debug logging
    va_list args;
    va_start(args, format);

    char output[490];
    auto length = vsnprintf(output, sizeof(output), format, args);
    if (length >= sizeof(output)) {
        output[sizeof(output) - 1] = '\0';
    }

    va_end(args);
    OsOutputDebugString("CStatus: %s\n", output);
}

void CStatus::Prepend(STATUS_TYPE severity, const char* format, ...) {
    // TODO
    // Remove temporary console debug logging
    va_list args;
    va_start(args, format);

    char output[490];
    auto length = vsnprintf(output, sizeof(output), format, args);
    if (length >= sizeof(output)) {
        output[sizeof(output) - 1] = '\0';
    }

    va_end(args);
    OsOutputDebugString("CStatus: %s\n", output);
}

CStatus& GetGlobalStatusObj() {
    return CStatus::s_errorList;
}
