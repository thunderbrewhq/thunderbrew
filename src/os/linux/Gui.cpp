#include "os/Gui.hpp"
#if defined(WHOA_BUILD_GLSDL)
#include "os/sdl/Gui.hpp"
#endif

static void* s_GxDevWindow = nullptr;

void* OsGuiGetWindow(int32_t type) {
    switch (type) {
    case 0:
    case 1:
    case 2:
        return s_GxDevWindow;
    default:
        return nullptr;
    }
}

bool OsGuiIsModifierKeyDown(int32_t key) {
    // TODO
    return false;
}

int32_t OsGuiProcessMessage(void* message) {
    return 0;
}

void OsGuiSetGxWindow(void* window) {
    s_GxDevWindow = window;
}

#if defined(WHOA_BUILD_GLSDL)

int32_t OsGuiMessageBox(void* parentWindow, int32_t style, const char* message, const char* title) {
    return OsSDLGuiMessageBox(parentWindow, style, message, title);
}

void OsGuiSetWindowTitle(void* window, const char* title) {
    return OsSDLGuiSetWindowTitle(window, title);
}

#else

int32_t OsGuiMessageBox(void* parentWindow, int32_t style, const char* message, const char* title) {
    return 1;
}

void OsGuiSetWindowTitle(void* window, const char* title) {
}

#endif
