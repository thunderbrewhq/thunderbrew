#include "ui/LuaExtraFuncs.hpp"
#include "ui/FrameScript.hpp"
#include "ui/FrameScriptInternal.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"
#include "os/Debug.hpp"
#include <cstdint>


static bool s_luaDecimalConversion = false;


luaL_Reg FrameScriptInternal::extra_funcs[31] = {
    { "setglobal", &sub_8168D0 },
    { "getglobal", &sub_816910 },
    { "strtrim", &strtrim },
    { "strsplit", &strsplit },
    { "strjoin", &strjoin },
    { "strreplace", &sub_816C40 },
    { "strconcat", &sub_816D80 },
    { "strlenutf8", &strlenutf8 },
    { "issecure", &issecure },
    { "issecurevariable", &issecurevariable },
    { "forceinsecure", &forceinsecure },
    { "securecall", &securecall },
    { "hooksecurefunc", &hooksecurefunc },
    { "debugload", &debugload },
    { "debuginfo", &debuginfo },
    { "debugprint", &debugprint },
    { "debugdump", &debugdump },
    { "debugbreak", &debugbreak },
    { "debughook", &debughook },
    { "debugtimestamp", &debugtimestamp },
    { "debugprofilestart", &debugprofilestart },
    { "debugprofilestop", &debugprofilestop },
    { "seterrorhandler", &seterrorhandler },
    { "geterrorhandler", &geterrorhandler },
    { "date", &os_date },
    { "time", &os_time },
    { "difftime", &os_difftime },
    { "debugstack", &debugstack },
    { "debuglocals", &debuglocals },
    { "scrub", &scrub },
    { nullptr, nullptr }
};

int32_t sub_8168D0(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t sub_816910(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t strtrim(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t strsplit(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t strjoin(lua_State* L) {
    size_t length = 0;
    auto v9 = luaL_checklstring(L, 1, &length);
    int32_t v1 = lua_gettop(L);
    int32_t v2 = v1 - 1;
    if (length) {
        if (v1 == 1) {
            lua_pushstring(L, "");
            return 1;
        } else {
            int32_t v4 = 2 * v2;
            int32_t v8 = 2 * v2;
            if (!lua_checkstack(L, 2 * v2))
                return luaL_error(L, "strjoin(): Stack overflow");
            if (v2 > 1) {
                int32_t v5 = 3;
                int32_t v6 = v2 - 1;
                do {
                    lua_pushlstring(L, v9, length);
                    lua_insert(L, v5);
                    v5 += 2;
                    --v6;
                } while (v6);
                v4 = v8;
            }
            lua_concat(L, v4 - 1);
            return 1;
        }
    } else {
        lua_concat(L, v1);
        return 1;
    }
}

int32_t sub_816C40(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t sub_816D80(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t strlenutf8(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t issecure(lua_State* L) {
    // TODO
    lua_pushnil(L);
    return 1;
}

int32_t issecurevariable(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t forceinsecure(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t securecall(lua_State* L) {
    // TODO: tainted
    if (lua_isstring(L, 1)) {
        lua_pushstring(L, lua_tolstring(L, 1, nullptr));
        lua_rawget(L, LUA_GLOBALSINDEX);
        lua_remove(L, 1);
        lua_insert(L, 1);
    }
    if (!lua_gettop(L)) {
        lua_pushnil(L);
    }

    lua_rawgeti(L, LUA_REGISTRYINDEX, FrameScript::s_errorHandlerRef);
    lua_insert(L, 1);
    if (lua_pcall(L, lua_gettop(L) - 2, -1, 1)) {
        lua_settop(L, -3);
    } else {
        lua_remove(L, 1);
    }
    // TODO: tainted
    return lua_gettop(L);
}

int32_t hooksecurefunc(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t debugload(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t debuginfo(lua_State* L) {
    return 0;
}

int32_t debugprint(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t debugdump(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t debugbreak(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t debughook(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t debugtimestamp(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t debugprofilestart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t debugprofilestop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t seterrorhandler(lua_State* L) {
    if (lua_type(L, 1) != LUA_TFUNCTION) {
        luaL_error(L, "Usage: seterrorhandler(errfunc)");
        return 0;
    }

    if (FrameScript::s_errorHandlerFun != -1) {
        luaL_unref(L, LUA_REGISTRYINDEX, FrameScript::s_errorHandlerFun);
    }

    FrameScript::s_errorHandlerFun = luaL_ref(L, LUA_REGISTRYINDEX);

    return 0;
}

int32_t geterrorhandler(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t os_date(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t os_time(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t os_difftime(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t debugstack(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t debuglocals(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t scrub(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t lua_setdecimalconversion(int32_t enabled) {
    s_luaDecimalConversion = (enabled != 0);
    return static_cast<int32_t>(s_luaDecimalConversion);
}

void lua_convertdecimal(char* string) {
    if (!s_luaDecimalConversion) {
        return;
    }

    size_t length = SStrLen(string);
    if (!length) {
        return;
    }

    char* end = &string[length];
    while (string < end) {
        if (*string < '0' || *string > '9') {
            ++string;
            continue;
        }

        char ch;
        while (true) {
            ch = *string;

            if ((ch < '0' || ch > '9') && ch != '.') {
                break;
            }

            if (ch == ',') {
LABEL_13:
                if (string[1] >= '0' && string[1] <= '9') {
                    *string = '.';
                }
            } else {
                if (ch == '.' && (string[1] < '0' || string[1] > '9')) {
                    *string = ',';
                }
            }
            ++string;
        }
        if (ch == ',') {
            goto LABEL_13;
        }

        ++string;
    }
}
