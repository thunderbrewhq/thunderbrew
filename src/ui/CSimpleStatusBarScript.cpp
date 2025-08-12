#include "ui/CSimpleStatusBarScript.hpp"
#include "ui/CSimpleStatusBar.hpp"
#include "ui/CSimpleTexture.hpp"
#include "ui/Util.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"
#include "util/StringTo.hpp"

static int32_t Script_GetOrientation(lua_State* L) {
    auto type = CSimpleStatusBar::GetObjectType();
    auto statusBar = static_cast<CSimpleStatusBar*>(FrameScript_GetObjectThis(L, type));
    lua_pushstring(L, OrientationToString(statusBar->m_orientation));
    return 1;
}

static int32_t Script_SetOrientation(lua_State* L) {
    auto type = CSimpleStatusBar::GetObjectType();
    auto statusBar = static_cast<CSimpleStatusBar*>(FrameScript_GetObjectThis(L, type));
    if (!lua_isstring(L, 2)) {
        return luaL_error(L, "Usage: %s:SetOrientation(\"orientation\")", statusBar->GetDisplayName());
    }

    auto string = lua_tolstring(L, 2, nullptr);
    uint32_t orientation = 0;
    if (!StringToOrientation(string, orientation)) {
        return luaL_error(L, "%s:SetOrientation(): Unknown orientation: %s", statusBar->GetDisplayName(), string);
    }

    statusBar->SetOrientation(orientation);
    return 0;
}

static int32_t Script_GetMinMaxValues(lua_State* L) {
    auto type = CSimpleStatusBar::GetObjectType();
    auto statusBar = static_cast<CSimpleStatusBar*>(FrameScript_GetObjectThis(L, type));
    lua_pushnumber(L, statusBar->m_minValue);
    lua_pushnumber(L, statusBar->m_maxValue);
    return 2;
}

static int32_t Script_SetMinMaxValues(lua_State* L) {
    auto type = CSimpleStatusBar::GetObjectType();
    auto statusBar = static_cast<CSimpleStatusBar*>(FrameScript_GetObjectThis(L, type));
    if (!lua_isnumber(L, 2) || !lua_isnumber(L, 3)) {
        return luaL_error(L, "Usage: %s:SetMinMaxValues(min, max)", statusBar->GetDisplayName());
    }

    auto minval = lua_tonumber(L, 2);
    auto maxval = lua_tonumber(L, 3);
    if (minval < -1.0e12 || minval > 1.0e12 || maxval < -1.0e12 || maxval > 1.0e12) {
        return luaL_error(L, "Min or Max out of range");
    }
    if (maxval - minval > 1.0e12) {
        return luaL_error(L, "Min and Max too far apart");
    }
    statusBar->SetMinMaxValues(minval, maxval);
    return 0;
}

static int32_t Script_GetValue(lua_State* L) {
    auto type = CSimpleStatusBar::GetObjectType();
    auto statusBar = static_cast<CSimpleStatusBar*>(FrameScript_GetObjectThis(L, type));
    lua_pushnumber(L, statusBar->m_value);
    return 1;
}

static int32_t Script_SetValue(lua_State* L) {
    auto type = CSimpleStatusBar::GetObjectType();
    auto statusBar = static_cast<CSimpleStatusBar*>(FrameScript_GetObjectThis(L, type));
    if (!lua_isnumber(L, 2)) {
        return luaL_error(L, "Usage: %s:SetValue(value)", statusBar->GetDisplayName());
    }

    auto value = lua_tonumber(L, 2);
    statusBar->SetValue(value);
    return 0;
}

static int32_t Script_GetStatusBarTexture(lua_State* L) {
    auto type = CSimpleStatusBar::GetObjectType();
    auto statusBar = static_cast<CSimpleStatusBar*>(FrameScript_GetObjectThis(L, type));
    auto texture = statusBar->m_barTexture;
    if (texture) {
        if (!texture->lua_registered) {
            texture->RegisterScriptObject(nullptr);
        }
        lua_rawgeti(L, LUA_REGISTRYINDEX, texture->lua_objectRef);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

static int32_t Script_SetStatusBarTexture(lua_State* L) {
    auto type = CSimpleStatusBar::GetObjectType();
    auto statusBar = static_cast<CSimpleStatusBar*>(FrameScript_GetObjectThis(L, type));

    int32_t layer = 2;

    if (lua_isstring(L, 3)) {
        StringToDrawLayer(lua_tolstring(L, 3, nullptr), layer);
    }

    if (lua_type(L, 2) == LUA_TTABLE) {
        lua_rawgeti(L, 2, 0);
        auto texture = static_cast<CSimpleTexture*>(lua_touserdata(L, -1));
        lua_settop(L, -2);

        if (!texture) {
            return luaL_error(L, "%s:SetStatusBarTexture(): Couldn't find 'this' in texture", statusBar->GetDisplayName());
        } else {
            auto textureType = CSimpleTexture::GetObjectType();
            if (!texture->IsA(textureType)) {
                return luaL_error(L, "%s:SetStatusBarTexture(): Wrong object type, expected texture", statusBar->GetDisplayName());
            }
        }

        statusBar->SetBarTexture(texture, layer);
        return 0;
    } 

    if (lua_isstring(L, 2)) {
        auto texFile = lua_tostring(L, 2);
        statusBar->SetBarTexture(texFile, layer);
        return 0;
    }

    if (lua_type(L, 2) != LUA_TNIL) {
        luaL_error(L, "Usage: %s:SetStatusBarTexture(texture or \"texture\" or nil [, \"layer\"])", statusBar->GetDisplayName());
    }

    statusBar->SetBarTexture(static_cast<CSimpleTexture*>(nullptr), 2);
    return 0;
}

static int32_t Script_GetStatusBarColor(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetStatusBarColor(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetRotatesTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetRotatesTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}


FrameScript_Method SimpleStatusBarMethods[NUM_SIMPLE_STATUS_BAR_SCRIPT_METHODS] = {
    { "GetOrientation", &Script_GetOrientation },
    { "SetOrientation", &Script_SetOrientation },
    { "GetMinMaxValues", &Script_GetMinMaxValues },
    { "SetMinMaxValues", &Script_SetMinMaxValues },
    { "GetValue", &Script_GetValue },
    { "SetValue", &Script_SetValue },
    { "GetStatusBarTexture", &Script_GetStatusBarTexture },
    { "SetStatusBarTexture", &Script_SetStatusBarTexture },
    { "GetStatusBarColor", &Script_GetStatusBarColor },
    { "SetStatusBarColor", &Script_SetStatusBarColor },
    { "GetRotatesTexture", &Script_GetRotatesTexture },
    { "SetRotatesTexture", &Script_SetRotatesTexture }
};
