#ifndef OS_SDL_GUI_HPP
#define OS_SDL_GUI_HPP

#include <cstdint>

int32_t OsSDLGuiMessageBox(void* parentWindow, int32_t style, const char* message, const char* title);

void OsSDLGuiSetWindowTitle(void* window, const char* title);

#endif
