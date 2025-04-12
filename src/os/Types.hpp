#ifndef OS_TYPES_HPP
#define OS_TYPES_HPP

#include <cstdint>

enum OSINPUT {
    OS_INPUT_CAPTURE_CHANGED        = 0,
    OS_INPUT_CHAR                   = 1,
    OS_INPUT_STRING                 = 2,
    OS_INPUT_IME                    = 3,
    OS_INPUT_SIZE                   = 4,
    OS_INPUT_CLOSE                  = 5,
    OS_INPUT_FOCUS                  = 6,
    OS_INPUT_KEY_DOWN               = 7,
    OS_INPUT_KEY_UP                 = 8,
    OS_INPUT_MOUSE_DOWN             = 9,
    OS_INPUT_MOUSE_MOVE             = 10,
    OS_INPUT_MOUSE_WHEEL            = 11,
    OS_INPUT_MOUSE_MOVE_RELATIVE    = 12,
    OS_INPUT_MOUSE_UP               = 13,
    OS_INPUT_14                     = 14,
    OS_INPUT_15                     = 15,
    OS_INPUT_16                     = 16,
    OS_INPUT_17                     = 17,
    OS_INPUT_18                     = 18,
    OS_INPUT_SHUTDOWN               = 19
};

enum OS_MOUSE_MODE {
    OS_MOUSE_MODE_NORMAL            = 0,
    OS_MOUSE_MODE_RELATIVE          = 1,
    OS_MOUSE_MODES                  = 2,
};

struct OSEVENT {
    OSINPUT id;
    int32_t param[4];
};

#endif
