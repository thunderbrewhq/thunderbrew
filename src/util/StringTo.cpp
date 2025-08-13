#include "util/StringTo.hpp"
#include "util/Lua.hpp"
#include <storm/String.hpp>
#include <utility>

uint64_t StringToClickAction(const char* actionStr) {
    if (!actionStr || !*actionStr) {
        return 0;
    }

    if (!SStrCmpI(actionStr, "LeftButtonDown", STORM_MAX_STR)) {
        return 1;
    }

    if (!SStrCmpI(actionStr, "LeftButtonUp", STORM_MAX_STR)) {
        return 0x80000000;
    }

    if (!SStrCmpI(actionStr, "MiddleButtonDown", STORM_MAX_STR)) {
        return 2;
    }

    if (!SStrCmpI(actionStr, "MiddleButtonUp", STORM_MAX_STR)) {
        return 0;
    }

    if (!SStrCmpI(actionStr, "RightButtonDown", STORM_MAX_STR)) {
        return 4;
    }

    if (!SStrCmpI(actionStr, "RightButtonUp", STORM_MAX_STR)) {
        return 0;
    }

    // TODO remaining buttons

    return 0;
}

int32_t StringToBOOL(const char* str) {
    return StringToBOOL(str, 0);
}

bool StringToBOOL(const char* str, int32_t def) {
    if (!str) {
        return def;
    }

    switch (*str) {
        case '0':
        case 'F':
        case 'N':
        case 'f':
        case 'n':
            return false;

        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case 'T':
        case 'Y':
        case 't':
        case 'y':
            return true;

        default:
            if (!SStrCmpI(str, "off", 0x7FFFFFFFu) || !SStrCmpI(str, "disabled", 0x7FFFFFFFu)) {
                return false;
            }

            if (!SStrCmpI(str, "on", 0x7FFFFFFFu) || !SStrCmpI(str, "enabled", 0x7FFFFFFFu)) {
                return true;
            }

            return def;
    }
}

bool StringToBOOL(lua_State* L, int32_t idx, int32_t def) {
    bool result;
    const char* str;

    switch (lua_type(L, idx)) {
        case LUA_TNIL:
            result = false;
            break;

        case LUA_TBOOLEAN:
            result = lua_toboolean(L, idx);
            break;

        case LUA_TNUMBER:
            result = lua_tonumber(L, idx) != 0;
            break;

        case LUA_TSTRING:
            str = lua_tolstring(L, idx, 0);
            result = StringToBOOL(str, def);
            break;

        default:
            result = def;
            break;
    }

    return result;
}

int32_t StringToDrawLayer(const char* string, int32_t& layer) {
    struct drawlayer {
        int32_t layer;
        const char* string;
    };

    static drawlayer array_drawlayer[5] = {
        { 0, "BACKGROUND" },
        { 1, "BORDER" },
        { 2, "ARTWORK" },
        { 3, "OVERLAY" },
        { 4, "HIGHLIGHT" }
    };

    for (int32_t i = 0; i < 5; i++) {
        if (!SStrCmpI(array_drawlayer[i].string, string, 0x7FFFFFFFu)) {
            layer = array_drawlayer[i].layer;
            return 1;
        }
    }

    return 0;
}

int32_t StringToJustify(const char* string, uint32_t& justify) {
    struct JustifyEntry {
        uint32_t value;
        const char* string;
    };

    static JustifyEntry justifyMap[6] = {
        { 0x1,  "LEFT" },
        { 0x2,  "CENTER" },
        { 0x4,  "RIGHT" },
        { 0x8,  "TOP" },
        { 0x10, "MIDDLE" },
        { 0x20, "BOTTOM" }
    };

    for (int32_t i = 0; i < 6; i++) {
        if (!SStrCmpI(justifyMap[i].string, string, 0x7FFFFFFFu)) {
            justify = justifyMap[i].value;
            return 1;
        }
    }

    return 0;
}

bool StringToOrientation(const char* string, uint32_t& orientation) {
    if (!SStrCmpI(string, "HORIZONTAL", STORM_MAX_STR)) {
        orientation = 0;
        return true;
    } else if (!SStrCmpI(string, "VERTICAL", STORM_MAX_STR)) {
        orientation = 1;
        return true;
    }
    return false;
}

bool StringToAnchorPoint(const char* string, int32_t& point) {
    static std::pair<int32_t, const char*> table[12] = {
        { 0, "ANCHOR_LEFT" },
        { 1, "ANCHOR_RIGHT" },
        { 2, "ANCHOR_BOTTOMLEFT" },
        { 3, "ANCHOR_BOTTOM" },
        { 4, "ANCHOR_BOTTOMRIGHT" },
        { 5, "ANCHOR_TOPLEFT" },
        { 6, "ANCHOR_TOP" },
        { 7, "ANCHOR_TOPRIGHT" },
        { 8, "ANCHOR_CURSOR" },
        { 9, "ANCHOR_NONE" },
        { 10, "ANCHOR_PRESERVE" },
        { 11, "ANCHOR_CURSOR_RIGHT" },
    };

    point = 0;

    for (size_t i = 0; i < 12; ++i) {
        if (!SStrCmpI(string, table[i].second, STORM_MAX_STR)) {
            point = table[i].first;
            return true;
        }
    }

    return false;
}
