#ifndef OS_SDL_INPUT_HPP
#define OS_SDL_INPUT_HPP

#include "os/Input.hpp"

bool OsSDLInputActive();

void OsSDLInputSetWindowResizeLock(int32_t resizeLock);

int32_t OsSDLInputGet(OSINPUT* id, int32_t* param0, int32_t* param1, int32_t* param2, int32_t* param3);

void OsSDLInputGetMousePosition(int32_t* x, int32_t *y);

#endif
