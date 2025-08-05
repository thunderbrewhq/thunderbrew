#include "gameui/CGCooldownScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"

static int32_t Script_SetCooldown(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetReverse(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetReverse(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetDrawEdge(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetDrawEdge(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}


FrameScript_Method CGCooldownMethods[NUM_CGCOOLDOWN_SCRIPT_METHODS] = {
    { "SetCooldown", &Script_SetCooldown },
    { "SetReverse", &Script_SetReverse },
    { "GetReverse", &Script_GetReverse },
    { "SetDrawEdge", &Script_SetDrawEdge },
    { "GetDrawEdge", &Script_GetDrawEdge }
};
