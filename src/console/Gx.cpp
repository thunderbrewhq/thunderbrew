#include "console/Gx.hpp"
#include <storm/String.hpp>
#include <cstdlib>

const char* g_gxApiNames[GxApis_Last] = {
    "OpenGL", // GxApi_OpenGl
    "D3D9",   // GxApi_D3d9
    "D3D9Ex", // GxApi_D3d9Ex
    "D3D10",  // GxApi_D3d10
    "D3D11",  // GxApi_D3d11
    "GLL",    // GxApi_GLL
    "GLSDL"   // GxApi_GLSDL
};

int32_t s_consoleGxOverrideSet[GxOverrides_Last];
uint32_t s_consoleGxOverrideVal[GxOverrides_Last];

void ConsoleGxOverride(const char* str) {
    char value[256];
    char override[256];

    while (*str) {
        SStrTokenize(&str, override, 256, " ,", 0);
        SStrTokenize(&str, value, 256, " ;", 0);

        if (override[0] && value[0]) {
            auto gxOverride = static_cast<EGxOverride>(std::atol(override));
            auto gxValue = std::atol(value);

            if (gxOverride < GxOverrides_Last) {
                if (gxOverride == 0) {
                    switch (gxValue) {
                    case 0:
                    case 1:
                    case 2:
                        gxValue = 1;
                        break;
                    case 3:
                        gxValue = 2;
                        break;
                    case 4:
                        gxValue = 3;
                        break;
                    case 5:
                        gxValue = 7;
                        break;
                    case 6:
                        gxValue = 8;
                        break;
                    case 7:
                        gxValue = 9;
                        break;
                    case 8:
                        gxValue = 10;
                        break;
                    case 10:
                        gxValue = 12;
                        break;
                    case 11:
                        gxValue = 13;
                        break;
                    default:
                        break;
                    }
                }

                s_consoleGxOverrideSet[gxOverride] = 1;
                s_consoleGxOverrideVal[gxOverride] = gxValue;
            }
        }
    }
}
