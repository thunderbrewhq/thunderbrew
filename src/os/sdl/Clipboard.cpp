#include "os/sdl/Clipboard.hpp"
#include <storm/String.hpp>

#include <SDL3/SDL_clipboard.h>

char* OsSDLClipboardGetString() {
    auto sdlText = SDL_GetClipboardText();
    auto text = SStrDupA(sdlText, __FILE__, __LINE__);
    SDL_free(sdlText);
    return text;
}

int32_t OsSDLClipboardPutString(const char* str) {
    return SDL_SetClipboardText(str);
}
