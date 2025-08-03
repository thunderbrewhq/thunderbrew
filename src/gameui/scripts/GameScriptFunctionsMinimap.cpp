#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_GetNumTrackingTypes(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetTrackingInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetTracking(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetTrackingTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void MinimapRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_MINIMAP; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_Minimap[i].name,
            GameScript::s_ScriptFunctions_Minimap[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_Minimap[NUM_SCRIPT_FUNCTIONS_MINIMAP] = {
    { "GetNumTrackingTypes", &Script_GetNumTrackingTypes },
    { "GetTrackingInfo", &Script_GetTrackingInfo },
    { "SetTracking", &Script_SetTracking },
    { "GetTrackingTexture", &Script_GetTrackingTexture },
};
