#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_SetLFGDungeon(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ClearLFGDungeon(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ClearAllLFGDungeons(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGInfoLocal(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGInfoServer(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGQueuedList(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetLFGComment(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_LFGTeleport(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_JoinLFG(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_LeaveLFG(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RefreshLFGList(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SearchLFGJoin(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SearchLFGGetJoinedID(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SearchLFGLeave(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SearchLFGGetNumResults(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SearchLFGGetResults(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SearchLFGGetEncounterResults(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SearchLFGGetPartyResults(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SearchLFGSort(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGTypes(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGRoleUpdate(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGRoleUpdateSlot(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGRoleUpdateMember(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGRoles(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetLFGRoles(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CompleteLFGRoleCheck(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGProposal(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGProposalMember(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGProposalEncounter(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AcceptProposal(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RejectProposal(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGBootProposal(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetLFGBootVote(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGQueueStats(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLastQueueStatusIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGDungeonInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGRandomDungeonInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsLFGDungeonJoinable(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetLFGHeaderCollapsed(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetLFGDungeonEnabled(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGCompletionReward(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGCompletionRewardItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsInLFGDungeon(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanPartyLFGBackfill(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPartyLFGBackfillInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PartyLFGStartBackfill(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGRandomCooldownExpiration(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_UnitHasLFGRandomCooldown(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGDeserterExpiration(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_UnitHasLFGDeserter(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAvailableRoles(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFDChoiceOrder(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFDChoiceInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFDChoiceCollapseState(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFDChoiceEnabledState(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFDChoiceLockedState(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFDLockPlayerCount(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFDLockInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RequestLFDPlayerLockInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RequestLFDPartyLockInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumRandomDungeons(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGDungeonRewards(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGDungeonRewardInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFGDungeonRewardLink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetRandomDungeonBestChoice(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLFRChoiceOrder(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsListedInLFR(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void LookingForGroupRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_LOOKING_FOR_GROUP; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_LookingForGroup[i].name,
            GameScript::s_ScriptFunctions_LookingForGroup[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_LookingForGroup[NUM_SCRIPT_FUNCTIONS_LOOKING_FOR_GROUP] = {
    { "SetLFGDungeon", &Script_SetLFGDungeon },
    { "ClearLFGDungeon", &Script_ClearLFGDungeon },
    { "ClearAllLFGDungeons", &Script_ClearAllLFGDungeons },
    { "GetLFGInfoLocal", &Script_GetLFGInfoLocal },
    { "GetLFGInfoServer", &Script_GetLFGInfoServer },
    { "GetLFGQueuedList", &Script_GetLFGQueuedList },
    { "SetLFGComment", &Script_SetLFGComment },
    { "LFGTeleport", &Script_LFGTeleport },
    { "JoinLFG", &Script_JoinLFG },
    { "LeaveLFG", &Script_LeaveLFG },
    { "RefreshLFGList", &Script_RefreshLFGList },
    { "SearchLFGJoin", &Script_SearchLFGJoin },
    { "SearchLFGGetJoinedID", &Script_SearchLFGGetJoinedID },
    { "SearchLFGLeave", &Script_SearchLFGLeave },
    { "SearchLFGGetNumResults", &Script_SearchLFGGetNumResults },
    { "SearchLFGGetResults", &Script_SearchLFGGetResults },
    { "SearchLFGGetEncounterResults", &Script_SearchLFGGetEncounterResults },
    { "SearchLFGGetPartyResults", &Script_SearchLFGGetPartyResults },
    { "SearchLFGSort", &Script_SearchLFGSort },
    { "GetLFGTypes", &Script_GetLFGTypes },
    { "GetLFGRoleUpdate", &Script_GetLFGRoleUpdate },
    { "GetLFGRoleUpdateSlot", &Script_GetLFGRoleUpdateSlot },
    { "GetLFGRoleUpdateMember", &Script_GetLFGRoleUpdateMember },
    { "GetLFGRoles", &Script_GetLFGRoles },
    { "SetLFGRoles", &Script_SetLFGRoles },
    { "CompleteLFGRoleCheck", &Script_CompleteLFGRoleCheck },
    { "GetLFGProposal", &Script_GetLFGProposal },
    { "GetLFGProposalMember", &Script_GetLFGProposalMember },
    { "GetLFGProposalEncounter", &Script_GetLFGProposalEncounter },
    { "AcceptProposal", &Script_AcceptProposal },
    { "RejectProposal", &Script_RejectProposal },
    { "GetLFGBootProposal", &Script_GetLFGBootProposal },
    { "SetLFGBootVote", &Script_SetLFGBootVote },
    { "GetLFGQueueStats", &Script_GetLFGQueueStats },
    { "GetLastQueueStatusIndex", &Script_GetLastQueueStatusIndex },
    { "GetLFGDungeonInfo", &Script_GetLFGDungeonInfo },
    { "GetLFGRandomDungeonInfo", &Script_GetLFGRandomDungeonInfo },
    { "IsLFGDungeonJoinable", &Script_IsLFGDungeonJoinable },
    { "SetLFGHeaderCollapsed", &Script_SetLFGHeaderCollapsed },
    { "SetLFGDungeonEnabled", &Script_SetLFGDungeonEnabled },
    { "GetLFGCompletionReward", &Script_GetLFGCompletionReward },
    { "GetLFGCompletionRewardItem", &Script_GetLFGCompletionRewardItem },
    { "IsInLFGDungeon", &Script_IsInLFGDungeon },
    { "CanPartyLFGBackfill", &Script_CanPartyLFGBackfill },
    { "GetPartyLFGBackfillInfo", &Script_GetPartyLFGBackfillInfo },
    { "PartyLFGStartBackfill", &Script_PartyLFGStartBackfill },
    { "GetLFGRandomCooldownExpiration", &Script_GetLFGRandomCooldownExpiration },
    { "UnitHasLFGRandomCooldown", &Script_UnitHasLFGRandomCooldown },
    { "GetLFGDeserterExpiration", &Script_GetLFGDeserterExpiration },
    { "UnitHasLFGDeserter", &Script_UnitHasLFGDeserter },
    { "GetAvailableRoles", &Script_GetAvailableRoles },
    { "GetLFDChoiceOrder", &Script_GetLFDChoiceOrder },
    { "GetLFDChoiceInfo", &Script_GetLFDChoiceInfo },
    { "GetLFDChoiceCollapseState", &Script_GetLFDChoiceCollapseState },
    { "GetLFDChoiceEnabledState", &Script_GetLFDChoiceEnabledState },
    { "GetLFDChoiceLockedState", &Script_GetLFDChoiceLockedState },
    { "GetLFDLockPlayerCount", &Script_GetLFDLockPlayerCount },
    { "GetLFDLockInfo", &Script_GetLFDLockInfo },
    { "RequestLFDPlayerLockInfo", &Script_RequestLFDPlayerLockInfo },
    { "RequestLFDPartyLockInfo", &Script_RequestLFDPartyLockInfo },
    { "GetNumRandomDungeons", &Script_GetNumRandomDungeons },
    { "GetLFGDungeonRewards", &Script_GetLFGDungeonRewards },
    { "GetLFGDungeonRewardInfo", &Script_GetLFGDungeonRewardInfo },
    { "GetLFGDungeonRewardLink", &Script_GetLFGDungeonRewardLink },
    { "GetRandomDungeonBestChoice", &Script_GetRandomDungeonBestChoice },
    { "GetLFRChoiceOrder", &Script_GetLFRChoiceOrder },
    { "IsListedInLFR", &Script_IsListedInLFR },
};
