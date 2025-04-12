#ifndef OS_SDL_CLIPBOARD_HPP
#define OS_SDL_CLIPBOARD_HPP

#include <cstdint>

char* OsSDLClipboardGetString();

int32_t OsSDLClipboardPutString(const char* str);

#endif
