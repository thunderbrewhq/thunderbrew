#ifndef OS_CLIPBOARD_HPP
#define OS_CLIPBOARD_HPP

#include <cstdint>

char* OsClipboardGetString();

int32_t OsClipboardPutString(const char*);

#endif
