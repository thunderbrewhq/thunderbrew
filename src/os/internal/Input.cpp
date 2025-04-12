#include "os/internal/Input.hpp"

int32_t s_numlockState;

uint32_t s_osButtonState;

OS_MOUSE_MODE s_osMouseMode;

int32_t s_windowFocused;

int32_t s_WindowResizeLock;

#if defined(WHOA_SYSTEM_WIN)

int32_t s_savedMouseSpeed;

#endif

#if defined(WHOA_SYSTEM_MAC)

double s_savedMouseSpeed;

#endif
