#include "os/Gui.hpp"
#include <storm/String.hpp>
#include <storm/Unicode.hpp>
#include <windows.h>
#include <malloc.h>

static void* s_GxDevWindow;

void* OsGuiGetWindow(int32_t type) {
    switch (type) {
    case 0:
        return s_GxDevWindow;
    case 1:
        return GetActiveWindow();
    case 2:
        return GetForegroundWindow();
    default:
        return nullptr;
    }
}

bool OsGuiIsModifierKeyDown(int32_t key) {
    // TODO
    return false;
}

int32_t OsGuiProcessMessage(void* message) {
    // TODO
    return 0;
}

void OsGuiSetGxWindow(void* window) {
    s_GxDevWindow = window;
}

int32_t OsGuiMessageBox(void* parentWindow, int32_t style, const char* message, const char* title) {
    auto messagelength = SUniConvertUTF8to16Len(reinterpret_cast<const uint8_t*>(message), STORM_MAX_STR, nullptr);
    auto messagebuffer = reinterpret_cast<uint16_t*>(alloca(2 * messagelength));
    SUniConvertUTF8to16(messagebuffer, messagelength, reinterpret_cast<const uint8_t*>(message), STORM_MAX_STR, nullptr, nullptr);

    title = title ? title : "";
    auto titlelength = SUniConvertUTF8to16Len(reinterpret_cast<const uint8_t*>(title), STORM_MAX_STR, nullptr);
    auto titlebuffer = reinterpret_cast<uint16_t*>(alloca(2 * titlelength));
    SUniConvertUTF8to16(titlebuffer, titlelength, reinterpret_cast<const uint8_t*>(title), STORM_MAX_STR, nullptr, nullptr);

    UINT type = 0;
    switch (style) {
    case 0:
        type = 0;
        break;
    case 1:
        type = MB_OKCANCEL;
        break;
    case 2:
        type = MB_YESNO;
        break;
    case 3:
        type = MB_YESNOCANCEL;
        break;
    }

    auto result = MessageBoxW(
        static_cast<HWND>(parentWindow),
        reinterpret_cast<LPCWSTR>(messagebuffer),
        reinterpret_cast<LPCWSTR>(titlebuffer),
        type);
    if (result == IDOK || result == IDYES) {
        return 0;
    }

    if (result == IDNO) {
        return 1;
    }
    return 2;
}

void OsGuiSetWindowTitle(void* window, const char* title) {
    auto widetitlelength = SUniConvertUTF8to16Len(reinterpret_cast<const uint8_t*>(title), STORM_MAX_STR, nullptr);
    auto widetitle = reinterpret_cast<uint16_t*>(alloca(2 * widetitlelength));
    SUniConvertUTF8to16(widetitle, widetitlelength, reinterpret_cast<const uint8_t*>(title), STORM_MAX_STR, nullptr, nullptr);
    SetWindowTextW(static_cast<HWND>(window), reinterpret_cast<LPCWSTR>(widetitle));
}
