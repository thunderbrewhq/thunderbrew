#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_GetArenaTeam(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumArenaTeamMembers(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetArenaTeamRosterInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetArenaTeamGdfInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetArenaTeamRosterSelection(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetArenaTeamRosterSelection(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SortArenaTeamRoster(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetArenaTeamRosterShowOffline(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetArenaTeamRosterShowOffline(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CloseArenaTeamRoster(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ArenaTeamRoster(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetCurrentArenaSeason(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPreviousArenaSeason(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void ArenaTeamInfoRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_ARENA_TEAM_INFO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_ArenaTeamInfo[i].name,
            GameScript::s_ScriptFunctions_ArenaTeamInfo[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_ArenaTeamInfo[NUM_SCRIPT_FUNCTIONS_ARENA_TEAM_INFO] = {
    { "GetArenaTeam", &Script_GetArenaTeam },
    { "GetNumArenaTeamMembers", &Script_GetNumArenaTeamMembers },
    { "GetArenaTeamRosterInfo", &Script_GetArenaTeamRosterInfo },
    { "GetArenaTeamGdfInfo", &Script_GetArenaTeamGdfInfo },
    { "SetArenaTeamRosterSelection", &Script_SetArenaTeamRosterSelection },
    { "GetArenaTeamRosterSelection", &Script_GetArenaTeamRosterSelection },
    { "SortArenaTeamRoster", &Script_SortArenaTeamRoster },
    { "SetArenaTeamRosterShowOffline", &Script_SetArenaTeamRosterShowOffline },
    { "GetArenaTeamRosterShowOffline", &Script_GetArenaTeamRosterShowOffline },
    { "CloseArenaTeamRoster", &Script_CloseArenaTeamRoster },
    { "ArenaTeamRoster", &Script_ArenaTeamRoster },
    { "GetCurrentArenaSeason", &Script_GetCurrentArenaSeason },
    { "GetPreviousArenaSeason", &Script_GetPreviousArenaSeason },
};
