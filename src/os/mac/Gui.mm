#include "os/Gui.hpp"

void* OsGuiGetWindow(int32_t type) {
    return nullptr;
}

bool OsGuiIsModifierKeyDown(int32_t key) {
    // TODO
    return false;
}

int32_t OsGuiProcessMessage(void* message) {
    return 0;
}

void OsGuiSetGxWindow(void* window) {
    // TODO
}

int32_t OsGuiMessageBox(void* parentWindow, int32_t style, const char* message, const char* title) {
    // TODO
    return 1;
}

void OsGuiSetWindowTitle(void* window, const char* title) {
    // TODO
}
