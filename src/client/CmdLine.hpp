#ifndef CLIENT_CMD_LINE_HPP
#define CLIENT_CMD_LINE_HPP

#include <cstdint>

enum CMDOPT {
    CMD_D3D = 0,
    CMD_D3D9EX = 1,
    CMD_DATA_DIR = 2,
    CMD_NO_LAG_FIX = 3,
    CMD_LOADFILE = 4,
    CMD_GAMETYPE = 5,
    CMD_OPENGL = 6,
    CMD_SW_TNL = 7,
    CMD_TIMEDEMO = 8,
    CMD_DEMOREZ = 9,
    CMD_DEMODEPTH = 10,
    CMD_DEMODETAIL = 11,
    CMD_DEMOSOUND = 12,
    CMD_FULL_SCREEN = 13,
    CMD_22050HZ = 14,
    CMD_NO_WARNINGS = 15,
    CMDOPTS
};

#define CMD_RES_800x600   static_cast<CMDOPT>(16)
#define CMD_RES_1024x768  static_cast<CMDOPT>(17)
#define CMD_RES_1280x960  static_cast<CMDOPT>(18)
#define CMD_RES_1280x1024 static_cast<CMDOPT>(19)
#define CMD_RES_1600x1200 static_cast<CMDOPT>(20)
#define CMD_UP_TO_DATE    static_cast<CMDOPT>(21)
#define CMD_16_BIT        static_cast<CMDOPT>(22)
#define CMD_NO_FIX_LAG    static_cast<CMDOPT>(24)
#define CMD_NO_SOUND      static_cast<CMDOPT>(26)
#define CMD_SOUND_CHAOS   static_cast<CMDOPT>(27)
#define CMD_DEPTH_16      static_cast<CMDOPT>(29)
#define CMD_DEPTH_24      static_cast<CMDOPT>(30)
#define CMD_DEPTH_32      static_cast<CMDOPT>(31)
#define CMD_WINDOWED      static_cast<CMDOPT>(32)
#define CMD_CONSOLE       static_cast<CMDOPT>(35)
#define CMD_HW_DETECT     static_cast<CMDOPT>(36)
#define CMD_GX_OVERRIDE   static_cast<CMDOPT>(39)

int32_t CmdLineProcess();

void ProcessCommandLine();

const char* CmdLineGetString(CMDOPT opt);

uint32_t CmdLineGetUint(CMDOPT opt);

int32_t CmdLineGetBool(CMDOPT opt);

#endif
