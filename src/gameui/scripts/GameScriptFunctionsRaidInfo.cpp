#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_GetNumRaidMembers(lua_State* L) {
    // TODO
    lua_pushnumber(L, 0.0);
    return 1;
}

static int32_t Script_GetRealNumRaidMembers(lua_State* L) {
    // TODO
    lua_pushnumber(L, 0.0);
    return 1;
}

static int32_t Script_GetRaidRosterInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetRaidRosterSelection(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetRaidRosterSelection(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsRaidLeader(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsRealRaidLeader(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsRaidOfficer(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetRaidSubgroup(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SwapRaidSubgroup(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ConvertToRaid(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PromoteToLeader(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PromoteToAssistant(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_DemoteAssistant(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetRaidTarget(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetRaidTargetIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_DoReadyCheck(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ConfirmReadyCheck(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetReadyCheckTimeLeft(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetReadyCheckStatus(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void RaidInfoRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_RAID_INFO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_RaidInfo[i].name,
            GameScript::s_ScriptFunctions_RaidInfo[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_RaidInfo[NUM_SCRIPT_FUNCTIONS_RAID_INFO] = {
    { "GetNumRaidMembers", &Script_GetNumRaidMembers },
    { "GetRealNumRaidMembers", &Script_GetRealNumRaidMembers },
    { "GetRaidRosterInfo", &Script_GetRaidRosterInfo },
    { "SetRaidRosterSelection", &Script_SetRaidRosterSelection },
    { "GetRaidRosterSelection", &Script_GetRaidRosterSelection },
    { "IsRaidLeader", &Script_IsRaidLeader },
    { "IsRealRaidLeader", &Script_IsRealRaidLeader },
    { "IsRaidOfficer", &Script_IsRaidOfficer },
    { "SetRaidSubgroup", &Script_SetRaidSubgroup },
    { "SwapRaidSubgroup", &Script_SwapRaidSubgroup },
    { "ConvertToRaid", &Script_ConvertToRaid },
    { "PromoteToLeader", &Script_PromoteToLeader },
    { "PromoteToAssistant", &Script_PromoteToAssistant },
    { "DemoteAssistant", &Script_DemoteAssistant },
    { "SetRaidTarget", &Script_SetRaidTarget },
    { "GetRaidTargetIndex", &Script_GetRaidTargetIndex },
    { "DoReadyCheck", &Script_DoReadyCheck },
    { "ConfirmReadyCheck", &Script_ConfirmReadyCheck },
    { "GetReadyCheckTimeLeft", &Script_GetReadyCheckTimeLeft },
    { "GetReadyCheckStatus", &Script_GetReadyCheckStatus },
};
