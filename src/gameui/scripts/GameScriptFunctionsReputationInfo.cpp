#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_GetNumFactions(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetFactionInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetFactionInfoByID(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetWatchedFactionInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetWatchedFactionIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_FactionToggleAtWar(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CollapseFactionHeader(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CollapseAllFactionHeaders(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetFactionInactive(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetFactionActive(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsFactionInactive(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ExpandFactionHeader(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ExpandAllFactionHeaders(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSelectedFaction(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSelectedFaction(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void ReputationInfoRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_REPUTATION_INFO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_ReputationInfo[i].name,
            GameScript::s_ScriptFunctions_ReputationInfo[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_ReputationInfo[NUM_SCRIPT_FUNCTIONS_REPUTATION_INFO] = {
    { "GetNumFactions", &Script_GetNumFactions },
    { "GetFactionInfo", &Script_GetFactionInfo },
    { "GetFactionInfoByID", &Script_GetFactionInfoByID },
    { "GetWatchedFactionInfo", &Script_GetWatchedFactionInfo },
    { "SetWatchedFactionIndex", &Script_SetWatchedFactionIndex },
    { "FactionToggleAtWar", &Script_FactionToggleAtWar },
    { "CollapseFactionHeader", &Script_CollapseFactionHeader },
    { "CollapseAllFactionHeaders", &Script_CollapseAllFactionHeaders },
    { "SetFactionInactive", &Script_SetFactionInactive },
    { "SetFactionActive", &Script_SetFactionActive },
    { "IsFactionInactive", &Script_IsFactionInactive },
    { "ExpandFactionHeader", &Script_ExpandFactionHeader },
    { "ExpandAllFactionHeaders", &Script_ExpandAllFactionHeaders },
    { "SetSelectedFaction", &Script_SetSelectedFaction },
    { "GetSelectedFaction", &Script_GetSelectedFaction },
};
