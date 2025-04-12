#ifndef OS_INTERNAL_INPUT_HPP
#define OS_INTERNAL_INPUT_HPP

#include "os/Types.hpp"

extern int32_t s_numlockState;

extern uint32_t s_osButtonState;

extern OS_MOUSE_MODE s_osMouseMode;

extern int32_t s_windowFocused;

extern int32_t s_WindowResizeLock;

#if defined(WHOA_SYSTEM_WIN)

extern int32_t s_savedMouseSpeed;

#endif

#if defined(WHOA_SYSTEM_MAC)

extern double s_savedMouseSpeed;

#endif

#endif
