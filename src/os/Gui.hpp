#ifndef OS_GUI_HPP
#define OS_GUI_HPP

#include <cstdint>

void* OsGuiGetWindow(int32_t type);

bool OsGuiIsModifierKeyDown(int32_t key);

int32_t OsGuiProcessMessage(void* message);

void OsGuiSetGxWindow(void* window);

int32_t OsGuiMessageBox(void* parentWindow, int32_t style, const char* message, const char* title);

void OsGuiSetWindowTitle(void* window, const char* title);

#endif
