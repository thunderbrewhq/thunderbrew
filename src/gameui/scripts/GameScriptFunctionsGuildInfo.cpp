#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_GetNumGuildMembers(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildRosterMOTD(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildRosterInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildRosterLastOnline(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GuildRosterSetPublicNote(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GuildRosterSetOfficerNote(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetGuildRosterSelection(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildRosterSelection(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanGuildPromote(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanGuildDemote(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanGuildInvite(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanGuildRemove(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanEditMOTD(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanEditPublicNote(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanEditOfficerNote(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanViewOfficerNote(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanEditGuildInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanGuildBankRepair(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanEditGuildTabInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanEditGuildEvent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SortGuildRoster(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetGuildRosterShowOffline(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildRosterShowOffline(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GuildControlGetNumRanks(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GuildControlGetRankName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GuildControlSetRank(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GuildControlGetRankFlags(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GuildControlSetRankFlag(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GuildControlSaveRank(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GuildControlAddRank(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GuildControlDelRank(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetGuildBankTabPermissions(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildBankTabPermissions(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetGuildBankWithdrawLimit(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildBankWithdrawLimit(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetGuildBankTabWithdraw(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CloseGuildRoster(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GuildRoster(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildInfoText(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetGuildInfoText(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_QueryGuildEventLog(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumGuildEvents(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildEventInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void GuildInfoRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_GUILD_INFO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_GuildInfo[i].name,
            GameScript::s_ScriptFunctions_GuildInfo[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_GuildInfo[NUM_SCRIPT_FUNCTIONS_GUILD_INFO] = {
    { "GetNumGuildMembers", &Script_GetNumGuildMembers },
    { "GetGuildRosterMOTD", &Script_GetGuildRosterMOTD },
    { "GetGuildRosterInfo", &Script_GetGuildRosterInfo },
    { "GetGuildRosterLastOnline", &Script_GetGuildRosterLastOnline },
    { "GuildRosterSetPublicNote", &Script_GuildRosterSetPublicNote },
    { "GuildRosterSetOfficerNote", &Script_GuildRosterSetOfficerNote },
    { "SetGuildRosterSelection", &Script_SetGuildRosterSelection },
    { "GetGuildRosterSelection", &Script_GetGuildRosterSelection },
    { "CanGuildPromote", &Script_CanGuildPromote },
    { "CanGuildDemote", &Script_CanGuildDemote },
    { "CanGuildInvite", &Script_CanGuildInvite },
    { "CanGuildRemove", &Script_CanGuildRemove },
    { "CanEditMOTD", &Script_CanEditMOTD },
    { "CanEditPublicNote", &Script_CanEditPublicNote },
    { "CanEditOfficerNote", &Script_CanEditOfficerNote },
    { "CanViewOfficerNote", &Script_CanViewOfficerNote },
    { "CanEditGuildInfo", &Script_CanEditGuildInfo },
    { "CanGuildBankRepair", &Script_CanGuildBankRepair },
    { "CanEditGuildTabInfo", &Script_CanEditGuildTabInfo },
    { "CanEditGuildEvent", &Script_CanEditGuildEvent },
    { "SortGuildRoster", &Script_SortGuildRoster },
    { "SetGuildRosterShowOffline", &Script_SetGuildRosterShowOffline },
    { "GetGuildRosterShowOffline", &Script_GetGuildRosterShowOffline },
    { "GuildControlGetNumRanks", &Script_GuildControlGetNumRanks },
    { "GuildControlGetRankName", &Script_GuildControlGetRankName },
    { "GuildControlSetRank", &Script_GuildControlSetRank },
    { "GuildControlGetRankFlags", &Script_GuildControlGetRankFlags },
    { "GuildControlSetRankFlag", &Script_GuildControlSetRankFlag },
    { "GuildControlSaveRank", &Script_GuildControlSaveRank },
    { "GuildControlAddRank", &Script_GuildControlAddRank },
    { "GuildControlDelRank", &Script_GuildControlDelRank },
    { "SetGuildBankTabPermissions", &Script_SetGuildBankTabPermissions },
    { "GetGuildBankTabPermissions", &Script_GetGuildBankTabPermissions },
    { "SetGuildBankWithdrawLimit", &Script_SetGuildBankWithdrawLimit },
    { "GetGuildBankWithdrawLimit", &Script_GetGuildBankWithdrawLimit },
    { "SetGuildBankTabWithdraw", &Script_SetGuildBankTabWithdraw },
    { "CloseGuildRoster", &Script_CloseGuildRoster },
    { "GuildRoster", &Script_GuildRoster },
    { "GetGuildInfoText", &Script_GetGuildInfoText },
    { "SetGuildInfoText", &Script_SetGuildInfoText },
    { "QueryGuildEventLog", &Script_QueryGuildEventLog },
    { "GetNumGuildEvents", &Script_GetNumGuildEvents },
    { "GetGuildEventInfo", &Script_GetGuildEventInfo },
};
