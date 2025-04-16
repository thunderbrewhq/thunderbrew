#include "client/CmdLine.hpp"
#include <storm/Command.hpp>

int32_t CmdLineProcess() {
    // engine-specific flags.
    static ARGLIST s_argList[] = {
        { 0x0,                       CMD_D3D,         "d3d",        nullptr },
        { 0x0,                       CMD_D3D9EX,      "d3d9ex",     nullptr },
        { STORM_COMMAND_TYPE_STRING, CMD_DATA_DIR,    "datadir",    nullptr },
        { 0x0,                       CMD_NO_LAG_FIX,  "nolagfix",   nullptr },
        { STORM_COMMAND_TYPE_STRING, CMD_LOADFILE,    "loadfile",   nullptr },
        { STORM_COMMAND_TYPE_STRING, CMD_GAMETYPE,    "gametype",   nullptr },
        { 0x0,                       CMD_OPENGL,      "opengl",     nullptr },
        { 0x0,                       CMD_SW_TNL,      "swtnl",      nullptr },
        { 0x0,                       CMD_TIMEDEMO,    "timedemo",   nullptr },
        { STORM_COMMAND_TYPE_STRING, CMD_DEMOREZ,     "rez",        nullptr },
        { STORM_COMMAND_TYPE_STRING, CMD_DEMODEPTH,   "depth",      nullptr },
        { STORM_COMMAND_TYPE_STRING, CMD_DEMODETAIL,  "detail",     nullptr },
        { STORM_COMMAND_TYPE_STRING, CMD_DEMOSOUND,   "sound",      nullptr },
        { 0x0,                       CMD_FULL_SCREEN, "fullscreen", nullptr },
        { 0x0,                       CMD_22050HZ,     "22050",      nullptr },
        { 0x0,                       CMD_NO_WARNINGS, "nowarnings", nullptr }
    };

    // load engine-specific launch flags
    SCmdRegisterArgList(s_argList, sizeof(s_argList) / sizeof(ARGLIST));

    // parse command line
    return SCmdProcessCommandLine(0, 0);
}

void ProcessCommandLine() {
    static ARGLIST s_wowArgList[] = {
        { 0x0,                       CMD_RES_800x600,   "800x600",    nullptr },
        { 0x0,                       CMD_RES_1024x768,  "1024x768",   nullptr },
        { 0x0,                       CMD_RES_1280x960,  "1280x960",   nullptr },
        { 0x0,                       CMD_RES_1280x1024, "1280x1024",  nullptr },
        { 0x0,                       CMD_RES_1600x1200, "1600x1200",  nullptr },
        { 0x0,                       CMD_16_BIT,        "16bit",      nullptr },
        { 0x0,                       CMD_UP_TO_DATE,    "uptodate",   nullptr },
        { 0x0,                       CMD_NO_SOUND,      "nosound",    nullptr },
        { 0x0,                       CMD_SOUND_CHAOS,   "soundchaos", nullptr },
        { 0x0,                       CMD_NO_FIX_LAG,    "nofixlag",   nullptr },
        { 0x0,                       CMD_DEPTH_16,      "d16",        nullptr },
        { 0x0,                       CMD_DEPTH_24,      "d24",        nullptr },
        { 0x0,                       CMD_DEPTH_32,      "d32",        nullptr },
        { 0x0,                       CMD_WINDOWED,      "windowed",   nullptr },
        { 0x0,                       CMD_HW_DETECT,     "hwdetect",   nullptr },
        { 0x0,                       CMD_CONSOLE,       "console",    nullptr },
        { STORM_COMMAND_TYPE_STRING, CMD_GX_OVERRIDE,   "gxoverride", nullptr }
    };

    // Load wow-specific launch flags
    SCmdRegisterArgList(s_wowArgList, sizeof(s_wowArgList) / sizeof(ARGLIST));

    CmdLineProcess();
}

const char* CmdLineGetString(CMDOPT opt) {
    static char buffer[260];

    SCmdGetString(opt, buffer, 260);

    return buffer;
}

uint32_t CmdLineGetUint(CMDOPT opt) {
    return SCmdGetNum(opt);
}

int32_t CmdLineGetBool(CMDOPT opt) {
    return SCmdGetBool(opt);
}
