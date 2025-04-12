#ifndef CONSOLE_TYPES_HPP
#define CONSOLE_TYPES_HPP

#include "gx/Font.hpp"
#include <storm/Hash.hpp>
#include <storm/List.hpp>

enum COLOR_T {
    DEFAULT_COLOR,
    INPUT_COLOR,
    ECHO_COLOR,
    ERROR_COLOR,
    WARNING_COLOR,
    GLOBAL_COLOR,
    ADMIN_COLOR,
    HIGHLIGHT_COLOR,
    BACKGROUND_COLOR,
    NUM_COLORTYPES,
};

enum CATEGORY {
    DEBUG,
    GRAPHICS,
    CONSOLE,
    COMBAT,
    GAME,
    DEFAULT,
    NET,
    SOUND,
    GM,
    NONE,
    LAST
};

enum EXECMODE {
    EM_PROMPTOVERWRITE = 0,
    EM_RECORDING = 1,
    EM_APPEND = 2,
    EM_WRITEFILE = 3,
    EM_NOTACTIVE = 4,
    EM_NUM_EXECMODES = 5
};

enum CONSOLERESIZESTATE {
    CS_NONE,
    CS_STRETCH,
    NUM_CONSOLERESIZESTATES,
};

typedef int32_t (*COMMANDHANDLER)(const char*, const char*);

#endif
