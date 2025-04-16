#include "os/sdl/Gui.hpp"
#include <SDL3/SDL.h>

static SDL_MessageBoxButtonData s_ok_button = { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "OK" };

static SDL_MessageBoxButtonData s_ok_cancel_buttons[2] = {
    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "OK" },
    { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Cancel" }
};

static SDL_MessageBoxButtonData s_yes_no_buttons[2] = {
    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Yes" },
    { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "No" }
};

static SDL_MessageBoxButtonData s_yes_no_cancel_buttons[3] = {
    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Yes" },
    { 0,                                       1, "No" },
    { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Cancel" }
};

int32_t OsSDLGuiMessageBox(void* parentWindow, int32_t style, const char* message, const char* title) {
    SDL_MessageBoxData box;
    box.flags       = 0;
    box.window      = static_cast<SDL_Window*>(parentWindow);
    box.title       = title;
    box.message     = message;
    box.colorScheme = nullptr;

    switch (style) {
    case 0:
        // type = MB_OK;
        box.numbuttons = 1;
        box.buttons    = &s_ok_button;
        break;
    case 1:
        // type = MB_OKCANCEL;
        box.numbuttons = 2;
        box.buttons = s_ok_cancel_buttons;
        break;
    case 2:
        // type = MB_YESNO;
        box.numbuttons = 2;
        box.buttons = s_yes_no_buttons;
        break;
    case 3:
        // type = MB_YESNOCANCEL;
        box.numbuttons = 3;
        box.buttons = s_yes_no_cancel_buttons;
        break;
    }

    int buttonid;
    SDL_ShowMessageBox(&box, &buttonid);
    return static_cast<int32_t>(buttonid);
}

void OsSDLGuiSetWindowTitle(void* window, const char* title) {
    if (window) {
        SDL_SetWindowTitle(static_cast<SDL_Window*>(window), title);
    }
}
