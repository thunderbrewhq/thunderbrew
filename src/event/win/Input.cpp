#include "event/Input.hpp"
#include "client/Gui.hpp"
#include <storm/Error.hpp>
#include <tempest/Vector.hpp>
#include <windows.h>

#if defined(WHOA_BUILD_GLSDL)
#include "event/sdl/Input.hpp"
#endif

static const uint32_t s_latin5lookup[256] = {
    0x00,   0x01,   0x02,   0x03,   0x04,   0x05,   0x06,   0x07,   0x08,
    0x09,   0x0A,   0x0B,   0x0C,   0x0D,   0x0E,   0x0F,   0x10,   0x11,
    0x12,   0x13,   0x14,   0x15,   0x16,   0x17,   0x18,   0x19,   0x1A,
    0x1B,   0x1C,   0x1D,   0x1E,   0x1F,   0x20,   0x21,   0x22,   0x23,
    0x24,   0x25,   0x26,   0x27,   0x28,   0x29,   0x2A,   0x2B,   0x2C,
    0x2D,   0x2E,   0x2F,   0x30,   0x31,   0x32,   0x33,   0x34,   0x35,
    0x36,   0x37,   0x38,   0x39,   0x3A,   0x3B,   0x3C,   0x3D,   0x3E,
    0x3F,   0x40,   0x41,   0x42,   0x43,   0x44,   0x45,   0x46,   0x47,
    0x48,   0x49,   0x4A,   0x4B,   0x4C,   0x4D,   0x4E,   0x4F,   0x50,
    0x51,   0x52,   0x53,   0x54,   0x55,   0x56,   0x57,   0x58,   0x59,
    0x5A,   0x5B,   0x5C,   0x5D,   0x5E,   0x5F,   0x60,   0x61,   0x62,
    0x63,   0x64,   0x65,   0x66,   0x67,   0x68,   0x69,   0x6A,   0x6B,
    0x6C,   0x6D,   0x6E,   0x6F,   0x70,   0x71,   0x72,   0x73,   0x74,
    0x75,   0x76,   0x77,   0x78,   0x79,   0x7A,   0x7B,   0x7C,   0x7D,
    0x7E,   0x7F,   0x20AC, 0x20,   0x201A, 0x192,  0x201E, 0x2026, 0x2020,
    0x2021, 0x2C6,  0x2030, 0x160,  0x2039, 0x152,  0x20,   0x20,   0x20,
    0x20,   0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014, 0x2DC,
    0x2122, 0x161,  0x203A, 0x153,  0x20,   0x20,   0x178,  0x0A0,  0x0A1,
    0x0A2,  0x0A3,  0x0A4,  0x0A5,  0x0A6,  0x0A7,  0x0A8,  0x0A9,  0x0AA,
    0x0AB,  0x0AC,  0x0AD,  0x0AE,  0x0AF,  0x0B0,  0x0B1,  0x0B2,  0x0B3,
    0x0B4,  0x0B5,  0x0B6,  0x0B7,  0x0B8,  0x0B9,  0x0BA,  0x0BB,  0x0BC,
    0x0BD,  0x0BE,  0x0BF,  0x0C0,  0x0C1,  0x0C2,  0x0C3,  0x0C4,  0x0C5,
    0x0C6,  0x0C7,  0x0C8,  0x0C9,  0x0CA,  0x0CB,  0x0CC,  0x0CD,  0x0CE,
    0x0CF,  0x11E,  0x0D1,  0x0D2,  0x0D3,  0x0D4,  0x0D5,  0x0D6,  0x0D7,
    0x0D8,  0x0D9,  0x0DA,  0x0DB,  0x0DC,  0x130,  0x15E,  0x0DF,  0x0E0,
    0x0E1,  0x0E2,  0x0E3,  0x0E4,  0x0E5,  0x0E6,  0x0E7,  0x0E8,  0x0E9,
    0x0EA,  0x0EB,  0x0EC,  0x0ED,  0x0EE,  0x0EF,  0x11F,  0x0F1,  0x0F2,
    0x0F3,  0x0F4,  0x0F5,  0x0F6,  0x0F7,  0x0F8,  0x0F9,  0x0FA,  0x0FB,
    0x0FC,  0x131,  0x15F,  0x0FF
};

static const uint32_t s_latin1lookup[32] = {
    0x0FFFE, 0x0FFFE, 0x201A, 0x192,  0x201E, 0x2026,  0x2020,  0x2021,
    0x2C6,   0x2030,  0x160,  0x2039, 0x152,  0x0FFFE, 0x0FFFE, 0x0FFFE,
    0x0FFFE, 0x2018,  0x2019, 0x201C, 0x201D, 0x2022,  0x2013,  0x2014,
    0x2DC,   0x2122,  0x161,  0x203A, 0x153,  0x0FFFE, 0x0FFFE, 0x178
};

static const uint32_t s_cyrilliclookup[256] = {
    0x00,   0x01,   0x02,   0x03,   0x04,   0x05,   0x06,   0x07,   0x08,
    0x09,   0x0A,   0x0B,   0x0C,   0x0D,   0x0E,   0x0F,   0x10,   0x11,
    0x12,   0x13,   0x14,   0x15,   0x16,   0x17,   0x18,   0x19,   0x1A,
    0x1B,   0x1C,   0x1D,   0x1E,   0x1F,   0x20,   0x21,   0x22,   0x23,
    0x24,   0x25,   0x26,   0x27,   0x28,   0x29,   0x2A,   0x2B,   0x2C,
    0x2D,   0x2E,   0x2F,   0x30,   0x31,   0x32,   0x33,   0x34,   0x35,
    0x36,   0x37,   0x38,   0x39,   0x3A,   0x3B,   0x3C,   0x3D,   0x3E,
    0x3F,   0x40,   0x41,   0x42,   0x43,   0x44,   0x45,   0x46,   0x47,
    0x48,   0x49,   0x4A,   0x4B,   0x4C,   0x4D,   0x4E,   0x4F,   0x50,
    0x51,   0x52,   0x53,   0x54,   0x55,   0x56,   0x57,   0x58,   0x59,
    0x5A,   0x5B,   0x5C,   0x5D,   0x5E,   0x5F,   0x60,   0x61,   0x62,
    0x63,   0x64,   0x65,   0x66,   0x67,   0x68,   0x69,   0x6A,   0x6B,
    0x6C,   0x6D,   0x6E,   0x6F,   0x70,   0x71,   0x72,   0x73,   0x74,
    0x75,   0x76,   0x77,   0x78,   0x79,   0x7A,   0x7B,   0x7C,   0x7D,
    0x7E,   0x7F,   0x402,  0x403,  0x201A, 0x453,  0x201E, 0x2026, 0x2020,
    0x2021, 0x20AC, 0x2030, 0x409,  0x2039, 0x40A,  0x40C,  0x40B,  0x40F,
    0x452,  0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014, 0x20,
    0x2122, 0x459,  0x203A, 0x45A,  0x45C,  0x45B,  0x45F,  0x0A0,  0x40E,
    0x45E,  0x408,  0x0A4,  0x490,  0x0A6,  0x0A7,  0x401,  0x0A9,  0x404,
    0x0AB,  0x0AC,  0x0AD,  0x0AE,  0x407,  0x0B0,  0x0B1,  0x406,  0x456,
    0x491,  0x0B5,  0x0B6,  0x0B7,  0x451,  0x2116, 0x454,  0x0BB,  0x458,
    0x405,  0x455,  0x457,  0x410,  0x411,  0x412,  0x413,  0x414,  0x415,
    0x416,  0x417,  0x418,  0x419,  0x41A,  0x41B,  0x41C,  0x41D,  0x41E,
    0x41F,  0x420,  0x421,  0x422,  0x423,  0x424,  0x425,  0x426,  0x427,
    0x428,  0x429,  0x42A,  0x42B,  0x42C,  0x42D,  0x42E,  0x42F,  0x430,
    0x431,  0x432,  0x433,  0x434,  0x435,  0x436,  0x437,  0x438,  0x439,
    0x43A,  0x43B,  0x43C,  0x43D,  0x43E,  0x43F,  0x440,  0x441,  0x442,
    0x443,  0x444,  0x445,  0x446,  0x447,  0x448,  0x449,  0x44A,  0x44B,
    0x44C,  0x44D,  0x44E,  0x44F
};

static const uint32_t s_latin2lookup[256] = {
    0x00,    0x01,    0x02,   0x03,    0x04,   0x05,    0x06,   0x07,   0x08,
    0x09,    0x0A,    0x0B,   0x0C,    0x0D,   0x0E,    0x0F,   0x10,   0x11,
    0x12,    0x13,    0x14,   0x15,    0x16,   0x17,    0x18,   0x19,   0x1A,
    0x1B,    0x1C,    0x1D,   0x1E,    0x1F,   0x20,    0x21,   0x22,   0x23,
    0x24,    0x25,    0x26,   0x27,    0x28,   0x29,    0x2A,   0x2B,   0x2C,
    0x2D,    0x2E,    0x2F,   0x30,    0x31,   0x32,    0x33,   0x34,   0x35,
    0x36,    0x37,    0x38,   0x39,    0x3A,   0x3B,    0x3C,   0x3D,   0x3E,
    0x3F,    0x40,    0x41,   0x42,    0x43,   0x44,    0x45,   0x46,   0x47,
    0x48,    0x49,    0x4A,   0x4B,    0x4C,   0x4D,    0x4E,   0x4F,   0x50,
    0x51,    0x52,    0x53,   0x54,    0x55,   0x56,    0x57,   0x58,   0x59,
    0x5A,    0x5B,    0x5C,   0x5D,    0x5E,   0x5F,    0x60,   0x61,   0x62,
    0x63,    0x64,    0x65,   0x66,    0x67,   0x68,    0x69,   0x6A,   0x6B,
    0x6C,    0x6D,    0x6E,   0x6F,    0x70,   0x71,    0x72,   0x73,   0x74,
    0x75,    0x76,    0x77,   0x78,    0x79,   0x7A,    0x7B,   0x7C,   0x7D,
    0x7E,    0x7F,    0x20AC, 0x0FFFE, 0x201A, 0x0FFFE, 0x201E, 0x2026, 0x2020,
    0x2021,  0x0FFFE, 0x2030, 0x160,   0x2039, 0x15A,   0x164,  0x17D,  0x179,
    0x0FFFE, 0x2018,  0x2019, 0x201C,  0x201D, 0x2022,  0x2013, 0x2014, 0x0FFFE,
    0x2122,  0x161,   0x203A, 0x15B,   0x165,  0x17E,   0x17A,  0x0A0,  0x2C7,
    0x2D8,   0x141,   0x0A4,  0x104,   0x0A6,  0x0A7,   0x0A8,  0x0A9,  0x15E,
    0x0AB,   0x0AC,   0x0AD,  0x0AE,   0x17B,  0x0B0,   0x0B1,  0x2DB,  0x142,
    0x0B4,   0x0B5,   0x0B6,  0x0B7,   0x0B8,  0x105,   0x15F,  0x0BB,  0x13D,
    0x2DD,   0x13E,   0x17C,  0x154,   0x0C1,  0x0C2,   0x102,  0x0C4,  0x139,
    0x106,   0x0C7,   0x10C,  0x0C9,   0x118,  0x0CB,   0x11A,  0x0CD,  0x0CE,
    0x10E,   0x110,   0x143,  0x147,   0x0D3,  0x0D4,   0x150,  0x0D6,  0x0D7,
    0x158,   0x16E,   0x0DA,  0x170,   0x0DC,  0x0DD,   0x162,  0x0DF,  0x155,
    0x0E1,   0x0E2,   0x103,  0x0E4,   0x13A,  0x107,   0x0E7,  0x10D,  0x0E9,
    0x119,   0x0EB,   0x11B,  0x0ED,   0x0EE,  0x10F,   0x111,  0x144,  0x148,
    0x0F3,   0x0F4,   0x151,  0x0F6,   0x0F7,  0x159,   0x16F,  0x0FA,  0x171,
    0x0FC,   0x0FD,   0x163,  0x2D9
};

static const uint32_t s_thailookup[256] = {
    0x00,   0x01,   0x02,   0x03,   0x04,   0x05,   0x06,   0x07,   0x08,
    0x09,   0x0A,   0x0B,   0x0C,   0x0D,   0x0E,   0x0F,   0x10,   0x11,
    0x12,   0x13,   0x14,   0x15,   0x16,   0x17,   0x18,   0x19,   0x1A,
    0x1B,   0x1C,   0x1D,   0x1E,   0x1F,   0x20,   0x21,   0x22,   0x23,
    0x24,   0x25,   0x26,   0x27,   0x28,   0x29,   0x2A,   0x2B,   0x2C,
    0x2D,   0x2E,   0x2F,   0x30,   0x31,   0x32,   0x33,   0x34,   0x35,
    0x36,   0x37,   0x38,   0x39,   0x3A,   0x3B,   0x3C,   0x3D,   0x3E,
    0x3F,   0x40,   0x41,   0x42,   0x43,   0x44,   0x45,   0x46,   0x47,
    0x48,   0x49,   0x4A,   0x4B,   0x4C,   0x4D,   0x4E,   0x4F,   0x50,
    0x51,   0x52,   0x53,   0x54,   0x55,   0x56,   0x57,   0x58,   0x59,
    0x5A,   0x5B,   0x5C,   0x5D,   0x5E,   0x5F,   0x60,   0x61,   0x62,
    0x63,   0x64,   0x65,   0x66,   0x67,   0x68,   0x69,   0x6A,   0x6B,
    0x6C,   0x6D,   0x6E,   0x6F,   0x70,   0x71,   0x72,   0x73,   0x74,
    0x75,   0x76,   0x77,   0x78,   0x79,   0x7A,   0x7B,   0x7C,   0x7D,
    0x7E,   0x7F,   0x20AC, 0x20,   0x20,   0x20,   0x20,   0x2026, 0x20,
    0x20,   0x20,   0x20,   0x20,   0x20,   0x20,   0x20,   0x20,   0x20,
    0x20,   0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014, 0x20,
    0x20,   0x20,   0x20,   0x20,   0x20,   0x20,   0x20,   0x0A0,  0x0E01,
    0x0E02, 0x0E03, 0x0E04, 0x0E05, 0x0E06, 0x0E07, 0x0E08, 0x0E09, 0x0E0A,
    0x0E0B, 0x0E0C, 0x0E0D, 0x0E0E, 0x0E0F, 0x0E10, 0x0E11, 0x0E12, 0x0E13,
    0x0E14, 0x0E15, 0x0E16, 0x0E17, 0x0E18, 0x0E19, 0x0E1A, 0x0E1B, 0x0E1C,
    0x0E1D, 0x0E1E, 0x0E1F, 0x0E20, 0x0E21, 0x0E22, 0x0E23, 0x0E24, 0x0E25,
    0x0E26, 0x0E27, 0x0E28, 0x0E29, 0x0E2A, 0x0E2B, 0x0E2C, 0x0E2D, 0x0E2E,
    0x0E2F, 0x0E30, 0x0E31, 0x0E32, 0x0E33, 0x0E34, 0x0E35, 0x0E36, 0x0E37,
    0x0E38, 0x0E39, 0x0E3A, 0x20,   0x20,   0x20,   0x20,   0x0E3F, 0x0E40,
    0x0E41, 0x0E42, 0x0E43, 0x0E44, 0x0E45, 0x0E46, 0x0E47, 0x0E48, 0x0E49,
    0x0E4A, 0x0E4B, 0x0E4C, 0x0E4D, 0x0E4E, 0x0E4F, 0x0E50, 0x0E51, 0x0E52,
    0x0E53, 0x0E54, 0x0E55, 0x0E56, 0x0E57, 0x0E58, 0x0E59, 0x0E5A, 0x0E5B,
    0x20,   0x20,   0x20,   0x20
};


static RECT s_defaultWindowRect;
static int32_t s_savedResize;

static HWND s_mouseWnd;
static C2iVector s_mousePos;

void CenterMouse() {
    // TODO
}

void RestoreMouse() {
    // TODO
}

void SaveMouse(HWND window, const POINT& pt) {
    s_mouseWnd = window;
    s_mousePos.x = static_cast<int32_t>(pt.x);
    s_mousePos.y = static_cast<int32_t>(pt.y);
}

int32_t ConvertButton(uint32_t message, uintptr_t wparam, MOUSEBUTTON* button) {
    switch (message) {
    case WM_NCLBUTTONDOWN:
    case WM_NCLBUTTONUP:
    case WM_NCLBUTTONDBLCLK:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP: {
        *button = MOUSE_BUTTON_LEFT;
        return 1;
    }

    case WM_NCRBUTTONDOWN:
    case WM_NCRBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP: {
        *button = MOUSE_BUTTON_RIGHT;
        return 1;
    }

    case WM_NCMBUTTONDOWN:
    case WM_NCMBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP: {
        *button = MOUSE_BUTTON_MIDDLE;
        return 1;
    }

    case WM_NCXBUTTONDOWN:
    case WM_NCXBUTTONUP:
    case WM_XBUTTONDOWN:
    case WM_XBUTTONUP: {
        switch (GET_XBUTTON_WPARAM(wparam)) {
        case XBUTTON1: {
            *button = MOUSE_BUTTON_XBUTTON1;
            return 1;
        }
        case XBUTTON2: {
            *button = MOUSE_BUTTON_XBUTTON2;
            return 1;
        }
        default: {
            *button = MOUSE_BUTTON_NONE;
            return 0;
        }
        }
    }

    default: {
        *button = MOUSE_BUTTON_NONE;
        return 0;
    }
    }
}

int32_t ConvertKeyCode(uint32_t vkey, KEY* key) {
    if (vkey >= VK_F1 && vkey <= VK_F12) {
        *key = static_cast<KEY>(KEY_F1 + (vkey - VK_F1));
        return 1;
    }

    if (vkey >= 0x30 && vkey <= 0x39) {
        *key = static_cast<KEY>(KEY_0 + (vkey - 0x30));
        return 1;
    }

    switch (vkey) {
    case VK_BACK: {
        *key = KEY_BACKSPACE;
        return 1;
    }

    case VK_TAB: {
        *key = KEY_TAB;
        return 1;
    }

    case VK_RETURN: {
        *key = KEY_ENTER;
        return 1;
    }

    case VK_PAUSE: {
        *key = KEY_PAUSE;
        return 1;
    }

    case VK_CAPITAL: {
        *key = KEY_CAPSLOCK;
        return 1;
    }

    case VK_ESCAPE: {
        *key = KEY_ESCAPE;
        return 1;
    }

    case VK_SPACE: {
        *key = KEY_SPACE;
        return 1;
    }

    case VK_PRIOR: {
        *key = KEY_PAGEUP;
        return 1;
    }

    case VK_NEXT: {
        *key = KEY_PAGEDOWN;
        return 1;
    }

    case VK_END: {
        *key = KEY_END;
        return 1;
    }

    case VK_HOME: {
        *key = KEY_HOME;
        return 1;
    }

    case VK_LEFT: {
        *key = KEY_LEFT;
        return 1;
    }

    case VK_UP: {
        *key = KEY_UP;
        return 1;
    }

    case VK_RIGHT: {
        *key = KEY_RIGHT;
        return 1;
    }

    case VK_DOWN: {
        *key = KEY_DOWN;
        return 1;
    }

    case VK_SNAPSHOT: {
        *key = KEY_PRINTSCREEN;
        return 1;
    }

    case VK_INSERT: {
        *key = KEY_INSERT;
        return 1;
    }

    case VK_DELETE: {
        *key = KEY_DELETE;
        return 1;
    }

    case VK_NUMPAD0:
    case VK_NUMPAD1:
    case VK_NUMPAD2:
    case VK_NUMPAD3:
    case VK_NUMPAD4:
    case VK_NUMPAD5:
    case VK_NUMPAD6:
    case VK_NUMPAD7:
    case VK_NUMPAD8:
    case VK_NUMPAD9: {
        *key = static_cast<KEY>(KEY_NUMPAD0 + (vkey - VK_NUMPAD0));
        return 1;
    }

    case VK_MULTIPLY: {
        *key = KEY_NUMPAD_MULTIPLY;
        return 1;
    }

    case VK_ADD: {
        *key = KEY_NUMPAD_PLUS;
        return 1;
    }

    case VK_SUBTRACT: {
        *key = KEY_NUMPAD_MINUS;
        return 1;
    }

    case VK_DECIMAL: {
        *key = KEY_NUMPAD_DECIMAL;
        return 1;
    }

    case VK_DIVIDE: {
        *key = KEY_NUMPAD_DIVIDE;
        return 1;
    }

    case VK_NUMLOCK: {
        *key = KEY_NUMLOCK;
        return 1;
    }

    case VK_SCROLL: {
        *key = KEY_SCROLLLOCK;
        return 1;
    }

    case VK_LSHIFT: {
        *key = KEY_LSHIFT;
        return 1;
    }

    case VK_RSHIFT: {
        *key = KEY_RSHIFT;
        return 1;
    }

    case VK_LCONTROL: {
        *key = KEY_LCONTROL;
        return 1;
    }

    case VK_RCONTROL: {
        *key = KEY_RCONTROL;
        return 1;
    }

    case VK_LMENU: {
        *key = KEY_LALT;
        return 1;
    }

    case VK_RMENU: {
        *key = KEY_RALT;
        return 1;
    }

    default: {
        auto character = MapVirtualKey(vkey, MAPVK_VK_TO_CHAR);
        *key = static_cast<KEY>(character);
        if (character && character <= 0xFF) {
            return 1;
        } else {
            return 0;
        }
    }
    }
}

bool ProcessMouseEvent(MOUSEBUTTON button, uint32_t message, HWND hwnd, OSINPUT id) {
    POINT mousePos;

    if (Input::s_osMouseMode == OS_MOUSE_MODE_RELATIVE) {
        // TODO
    } else {
        GetCursorPos(&mousePos);
        ScreenToClient(hwnd, &mousePos);
    }

    OsQueuePut(id, button, mousePos.x, mousePos.y, 0);

    return message == WM_XBUTTONDOWN
        || message == WM_XBUTTONUP
        || message == WM_NCXBUTTONDOWN
        || message == WM_NCXBUTTONUP;
}

int32_t HandleMouseDown(uint32_t message, uintptr_t wparam, bool* xbutton, HWND hwnd) {
    MOUSEBUTTON button;
    if (!ConvertButton(message, wparam, &button)) {
        return 0;
    }

    if (Input::s_osButtonState == 0) {
        SetCapture(hwnd);
    }

    Input::s_osButtonState |= button;

    auto xb = ProcessMouseEvent(button, message, hwnd, OS_INPUT_MOUSE_DOWN);

    if (xbutton) {
        *xbutton = xb;
    }

    return 1;
}

int32_t HandleMouseUp(uint32_t message, uintptr_t wparam, bool* xbutton, HWND hwnd) {
    MOUSEBUTTON button;
    if (!ConvertButton(message, wparam, &button)) {
        return 0;
    }

    Input::s_osButtonState &= ~button;

    if (Input::s_osButtonState == 0) {
        // TODO
        ReleaseCapture();
        // TODO
    }

    auto xb = ProcessMouseEvent(button, message, hwnd, OS_INPUT_MOUSE_UP);

    if (xbutton) {
        *xbutton = xb;
    }

    return 1;
}

int32_t OsInputGet(OSINPUT* id, int32_t* param0, int32_t* param1, int32_t* param2, int32_t* param3) {
#if defined(WHOA_BUILD_GLSDL)
    if (SDLInputActive()) {
        // SDL handles input events for us
        return SDLInputGet(id, param0, param1, param2, param3);
    }
#endif

    *id = static_cast<OSINPUT>(-1);

    if (s_savedResize) {
        auto hwnd = static_cast<HWND>(OsGuiGetWindow(0));

        if (!IsIconic(hwnd)) {
            s_savedResize = 0;

            RECT windowRect;
            GetWindowRect(hwnd, &windowRect);

            auto style = GetWindowLong(hwnd, GWL_STYLE);
            RECT clientArea = { 0, 0, 0, 0 };
            AdjustWindowRectEx(&clientArea, style, false, 0);

            auto width = windowRect.right - clientArea.right - (windowRect.left - clientArea.left);
            auto height = windowRect.bottom - clientArea.bottom - (windowRect.top - clientArea.top);

            if (s_defaultWindowRect.right != width || s_defaultWindowRect.bottom != height) {
                s_defaultWindowRect.left = 0;
                s_defaultWindowRect.top = 0;
                s_defaultWindowRect.right = width;
                s_defaultWindowRect.bottom = height;

                *id = OS_INPUT_SIZE;
                *param0 = width;
                *param1 = height;
                *param2 = 0;
                *param3 = 0;

                return 1;
            }
        }
    }

    if (Input::s_queueTail != Input::s_queueHead) {
        OsQueueGet(id, param0, param1, param2, param3);
        return 1;
    }

    // TODO Sub8714B0(dwordB1C220);

    while (true) {
        MSG msg;
        auto peekResult = PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE);

        if (Input::s_queueTail != Input::s_queueHead) {
            break;
        }

        if (!peekResult) {
            return 0;
        }

        if (!GetMessage(&msg, nullptr, 0, 0)) {
            *id = OS_INPUT_SHUTDOWN;
            break;
        }

        if (OsGuiProcessMessage(&msg)) {
            break;
        }

        if (Input::s_queueTail != Input::s_queueHead) {
            break;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (Input::s_queueTail != Input::s_queueHead) {
            break;
        }
    }

    OsQueueGet(id, param0, param1, param2, param3);
    return 1;
}

void OsInputSetMouseMode(OS_MOUSE_MODE mode) {
    STORM_ASSERT(mode < OS_MOUSE_MODES);
    STORM_VALIDATE(mode < OS_MOUSE_MODES, ERROR_INVALID_PARAMETER);

    if (Input::s_osMouseMode == mode) {
        return;
    }

    if (mode == OS_MOUSE_MODE_NORMAL) {
        Input::s_osMouseMode = mode;
        RestoreMouse();
    } else if (mode == OS_MOUSE_MODE_RELATIVE) {
        Input::s_osMouseMode = mode;
        CenterMouse();
    }
}

void OsInputGetMousePosition(int32_t* x, int32_t* y) {
#if defined(WHOA_BUILD_GLSDL)
    if (SDLInputActive()) {
        SDLInputGetMousePosition(x, y);
        return;
    }
#endif

    // Get HWND created by CGxDevice
    auto window = static_cast<HWND>(OsGuiGetWindow(0));

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(window, &pt);

    if (Input::s_osMouseMode != OS_MOUSE_MODE_RELATIVE) {
        SaveMouse(window, pt);
    }

    // Provide mouse position to caller
    if (x) {
        *x = static_cast<int32_t>(pt.x);
    }
    if (y) {
        *y = static_cast<int32_t>(pt.y);
    }
}

uint32_t OsInputGetCodePage() {
    return ::GetACP();
}

int32_t OsWindowProc(void* window, uint32_t message, uintptr_t wparam, intptr_t lparam) {
    static uint32_t s_codepage = 0;

    auto hwnd = static_cast<HWND>(window);

    // TODO

    switch (message) {
    // TODO handle remaining message types

    case WM_SIZE:
    case WM_DISPLAYCHANGE: {
        s_savedResize = lparam;
        break;
    }

    case WM_ACTIVATE: {
        auto isMinimized = IsIconic(hwnd);
        auto isActive = wparam != WA_INACTIVE;
        Input::s_windowFocused = isActive && !isMinimized;

        // TODO capture

        // TODO mouse speed

        OsQueuePut(OS_INPUT_FOCUS, Input::s_windowFocused != 0, 0, 0, 0);

        break;
    }

    case WM_CLOSE: {
        OsQueuePut(OS_INPUT_CLOSE, 0, 0, 0, 0);
        return 0;
    }

    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP: {
        auto keyDown = message == WM_KEYDOWN || message == WM_SYSKEYDOWN;

        if (wparam == VK_SHIFT) {
            // TODO
        } else if (wparam == VK_CONTROL) {
            // TODO
        } else if (wparam == VK_MENU) {
            // TODO
        }

        KEY key;
        if (ConvertKeyCode(wparam, &key)) {
            OsQueuePut(keyDown ? OS_INPUT_KEY_DOWN : OS_INPUT_KEY_UP, key, LOWORD(lparam), 0, 0);

            // Alt + F4
            if (key == KEY_F4 && OsGuiIsModifierKeyDown(2)) {
                break;
            }

            return 0;
        }

        break;
    }

    case WM_CHAR: {
        if (wparam < 32) {
            break;
        }

        uint32_t character = wparam;

        if (wparam >= 128) {
            if (s_codepage == 0) {
                s_codepage = OsInputGetCodePage();
            }
            if (s_codepage == 1254) {
                // ANSI Turkish; Turkish (Windows)
                character = s_latin5lookup[wparam % 256];
            } else if (s_codepage == 1252 && wparam < 0xA0) {
                // ANSI Latin 1; Western European (Windows)
                character = s_latin1lookup[wparam % 32];
            } else if (s_codepage == 1251) {
                // ANSI Cyrillic; Cyrillic (Windows)
                character = s_cyrilliclookup[wparam % 256];
            } else if (s_codepage == 1250) {
                // ANSI Central European; Central European (Windows)
                character = s_latin2lookup[wparam % 256];
            } else if (s_codepage == 874) {
                // Thai (Windows)
                character = s_thailookup[wparam % 256];
            }
        }

        OsQueuePut(OS_INPUT_CHAR, character, LOWORD(lparam), 0, 0);
        return 0;
    }

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_XBUTTONDOWN: {
        bool xbutton;
        if (HandleMouseDown(message, wparam, &xbutton, hwnd)) {
            // Normally, a processed button down message should return 0
            // In the case of xbuttons, a processed button down message should return 1
            // See: https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-xbuttondown
            return xbutton ? 1 : 0;
        }

        break;
    }

    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_XBUTTONUP: {
        if (message == WM_LBUTTONUP) {
            // TODO
        }

        bool xbutton;
        if (HandleMouseUp(message, wparam, &xbutton, hwnd)) {
            // Normally, a processed button down message should return 0
            // In the case of xbuttons, a processed button down message should return 1
            // See: https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-xbuttondown
            return xbutton ? 1 : 0;
        }

        break;
    }

    case WM_MOUSEMOVE: {
        // TODO

        if (Input::s_osMouseMode == OS_MOUSE_MODE_RELATIVE) {
            // TODO
        } else {
            POINT mousePos;
            GetCursorPos(&mousePos);
            ScreenToClient(hwnd, &mousePos);
            OsQueuePut(OS_INPUT_MOUSE_MOVE, 0, mousePos.x, mousePos.y, 0);
            SaveMouse(hwnd, mousePos);
        }

        break;
    }

    default:
        break;
    }

    // TODO

    return DefWindowProc(static_cast<HWND>(window), message, wparam, lparam);
}
