#ifndef CONSOLE_GX_HPP
#define CONSOLE_GX_HPP

#include <cstdint>
#include "gx/Types.hpp"

extern const char* g_gxApiNames[GxApis_Last];

extern int32_t s_consoleGxOverrideSet[GxOverrides_Last];
extern uint32_t s_consoleGxOverrideVal[GxOverrides_Last];

void ConsoleGxOverride(const char* str);

#endif
