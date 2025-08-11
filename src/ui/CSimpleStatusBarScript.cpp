#include "ui/CSimpleStatusBarScript.hpp"
#include "ui/CSimpleStatusBar.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"

static int32_t Script_GetOrientation(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetOrientation(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetMinMaxValues(lua_State* L) {
    auto type = CSimpleStatusBar::GetObjectType();
    auto statusBar = static_cast<CSimpleStatusBar*>(FrameScript_GetObjectThis(L, type));
    lua_pushnumber(L, statusBar->m_minValue);
    lua_pushnumber(L, statusBar->m_maxValue);
    return 2;
}

static int32_t Script_SetMinMaxValues(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetValue(lua_State* L) {
    auto type = CSimpleStatusBar::GetObjectType();
    auto statusBar = static_cast<CSimpleStatusBar*>(FrameScript_GetObjectThis(L, type));
    lua_pushnumber(L, statusBar->m_value);
    return 1;
}

static int32_t Script_SetValue(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetStatusBarTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetStatusBarTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
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
