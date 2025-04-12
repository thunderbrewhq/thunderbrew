#include "os/Clipboard.hpp"
#include "gx/Device.hpp"
#include "gx/Types.hpp"
#include <storm/String.hpp>
#include <windows.h>

char* IOsClipboardGetString(HWND window) {
    if (!OpenClipboard(window)) {
        return nullptr;
    }
    auto handle = GetClipboardData(CF_UNICODETEXT);
    auto widestr = reinterpret_cast<LPWSTR>(GlobalLock(handle));
    if (!widestr) {
        return nullptr;
    }

    // Get length of UTF-8 text
    auto length = WideCharToMultiByte(CP_UTF8, 0, widestr, -1, nullptr, 0, nullptr, nullptr);
    auto str = reinterpret_cast<char*>(SMemAlloc(length, __FILE__, __LINE__, 0x0));
    // Convert UTF-16 into UTF-8
    WideCharToMultiByte(CP_UTF8, 0, widestr, -1, str, length, nullptr, nullptr);
    str[length - 1] = '\0';

    GlobalUnlock(handle);
    CloseClipboard();

    return str;
}

int32_t IOsClipboardPutString(const char* str, HWND window) {
    // Allocate twice as large UTF-16 string
    auto length = SStrLen(str) + 1;
    auto memory = GlobalAlloc(GMEM_SHARE | GMEM_MOVEABLE | GMEM_ZEROINIT, length * 2);
    if (!memory) {
        return 0;
    }
    // Get access to global memory
    auto widestr = reinterpret_cast<LPWSTR>(GlobalLock(memory));
    if (!widestr) {
        GlobalFree(memory);
        return 0;
    }
    // Convert UTF-8 string into UTF-16 string
    MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, str, length - 1, widestr, length * 2);
    // Finish writing to memory
    GlobalUnlock(memory);

    // Copy UTF-16 text into clipboard
    if (!OpenClipboard(nullptr)) {
        GlobalFree(memory);
        return 0;
    }
    if (!EmptyClipboard()) {
        CloseClipboard();
        GlobalFree(memory);
        return 0;
    }
    SetClipboardData(CF_UNICODETEXT, memory);
    CloseClipboard();

    return 1;
}

int32_t OsClipboardPutString(const char* str) {
    return IOsClipboardPutString(str, GxDevApi() == GxApi_GLSDL ? static_cast<HWND>(nullptr) : static_cast<HWND>(GxDevWindow()));
}

char* OsClipboardGetString() {
    return IOsClipboardGetString(
        GxDevApi() == GxApi_GLSDL ?
        static_cast<HWND>(nullptr) :
        static_cast<HWND>(GxDevWindow()));
}
