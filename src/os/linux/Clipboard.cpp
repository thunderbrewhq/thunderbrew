#include "os/Clipboard.hpp"

#if defined(WHOA_BUILD_GLSDL)

#include "os/sdl/Clipboard.hpp"

char* OsClipboardGetString() {
    return OsSDLClipboardGetString();
}

int32_t OsClipboardPutString(const char* str) {
    return OsSDLClipboardPutString(str);
}

#else

char* OsClipboardGetString() {
    return nullptr;
}

int32_t OsClipboardPutString(const char* str) {
    return 0;
}

#endif
