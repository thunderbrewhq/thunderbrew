#include "ui/CSimpleMessageFrameScript.hpp"
#include "ui/CSimpleMessageFrame.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"

static int32_t Script_GetOrientation(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetOrientation(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetMinMaxValues(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetMinMaxValues(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetValue(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
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


FrameScript_Method SimpleMessageFrameMethods[NUM_SIMPLE_MESSAGE_FRAME_SCRIPT_METHODS] = {
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
